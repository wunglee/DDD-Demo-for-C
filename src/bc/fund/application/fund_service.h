#ifndef TRANSFER_FundService_H
#define TRANSFER_FundService_H

#include "../../../framework_components/domain_event/publish_subscribe_service.h"
#include "../../../framework_components/naming_service/naming_service_manager.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_dto.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_service_local_interface.h"
#include "fund_repository_interface.h"
#include "fund_service_query_interface.h"
class FundService : public FundServiceLocalInterface {
 private:
  FundRepositoryInterface* fund_Repository_Interface;
  FundServiceQueryInterface* fund_Service_Query_Interface;
  FundService(
      FundRepositoryInterface* fund_Repository_Interface,
      FundServiceQueryInterface* fund_Service_Query_Interface)
      : fund_Repository_Interface(fund_Repository_Interface),
        fund_Service_Query_Interface(fund_Service_Query_Interface) {}
  static FundService* fund_Service;

 public:
  virtual ~FundService() { FundService::fund_Service = nullptr; }
  static FundService* BuildInstance(
      FundRepositoryInterface* fund_Repository_Interface,
      FundServiceQueryInterface* fund_Service_Query_Interface) {
    assert(fund_Repository_Interface != nullptr && fund_Service_Query_Interface != nullptr);
    if (FundService::fund_Service == nullptr) {
      FundService::fund_Service =
          new FundService(fund_Repository_Interface, fund_Service_Query_Interface);
    }
    return FundService::fund_Service;
  }
  static void DestoryInstance() {
    if (FundService::fund_Service != nullptr) delete FundService::fund_Service;
  }
  static FundService* GetInstance() {
    if (FundService::fund_Service == nullptr) {
      throw "单例未创建";
    }
    return FundService::fund_Service;
  }
  virtual void Initialize(std::string account_id, float amount) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_id);
    fund.AddAmount(amount);
    fund_Repository_Interface->Update(fund);
  }
  virtual void Increase(int order_id, std::string account_name, float amount) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_name);
    if (fund.Is_Forbid_Out()) {
      PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
          "增资已失败",
          order_id,
          IncreaseFailDTO(
              order_id, Exception((boost::format("收款方禁止收款:%s") % account_name).str()))
              .Serialize()));
      return;
    }
    fund.AddAmount(amount);
    fund_Repository_Interface->Update(fund);
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
        "增资已成功", order_id, IncreaseSuccessDTO(order_id, account_name, amount).Serialize()));
  }
  virtual void Decrease(int order_id, std::string account_name, float amount) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_name);
    if (fund.IsForbidIn()) {
      PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
          "扣减已失败",
          order_id,
          DecreaseFailDTO(
              order_id, Exception((boost::format("付款方禁止转账:%s") % account_name).str()))
              .Serialize()));
      return;
    }
    if (!fund.Is_Enough(amount)) {
      PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
          "扣减已失败",
          order_id,
          DecreaseFailDTO(
              order_id, Exception((boost::format("付款方金额不足，少于%f元") % amount).str()))
              .Serialize()));
      return;
    }
    fund.SubAmount(amount);
    fund_Repository_Interface->Update(fund);
    PublishSubscribeService::BuildInstance()->Publish(
        DomainEvent("扣减已成功", order_id, std::to_string(order_id)));
  }
  virtual void SetForbidOut(std::string account_name, bool forbid) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_name);
    fund.SetForbidOut(forbid);
    fund_Repository_Interface->Update(fund);
  }
  virtual void SetForbidIn(std::string account_name, bool forbid) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_name);
    fund.SetForbidIn(forbid);
    fund_Repository_Interface->Update(fund);
  }
  virtual void AddFundAccount(std::string account_name) override {
    Fund fund(account_name);
    fund_Repository_Interface->Create(fund);
  }
  virtual boost::optional<FundDTO> GetFund(std::string name) override {
    boost::optional<Fund> fund_optional = fund_Service_Query_Interface->GetFund(name);
    if (fund_optional.has_value()) {
      Fund fund = fund_optional.value();
      return FundDTO(
          fund.GetAccount(),
          fund.IsForbidIn(),
          fund.Is_Forbid_Out(),
          fund.Get_Free_Amount(),
          fund.Get_Locked_Amount());
    }
    return boost::none;
  }
  bool LockAmount(std::string account_name, float amount) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_name);
    fund.Lock_Amount(amount);
    fund_Repository_Interface->Update(fund);
    return true;
  }
  void UnLockAmount(std::string account_name, float amount) override {
    Fund fund = fund_Repository_Interface->GetExisted(account_name);
    fund.UnLock_Amount(amount);
    fund_Repository_Interface->Update(fund);
  }
};
#endif  // TRANSFER_FundService_H
