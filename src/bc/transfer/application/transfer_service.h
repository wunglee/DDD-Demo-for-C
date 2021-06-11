#ifndef ARGS_TransferService_H
#define ARGS_TransferService_H

#include <string>

#include <boost/format.hpp>

#include "boost/optional.hpp"

#include "../../../framework_components/domain_event/domain_event.h"
#include "../../../framework_components/domain_event/publish_subscribe_service.h"
#include "../../../framework_components/exception.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_service_remote_interface.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_dto.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_service_interface.h"
#include "../../../global_business_dependency/service_interfaces/user/user_service_interface.h"
#include "../domain/transfer.h"
#include "transfer_query_interface.h"
#include "transfer_repository_interface.h"

/**
 * TODO::所有领域事件和仓储操作必须在一个强一致事务内
 */
class TransferService : public TransferServiceInterface {
 private:
  TransferRepositoryInterface* transferRepositoryInterface;
  TransferQueryInterface* transferQueryInterface;
  UserServiceInterface* userServiceInterface;
  FundServiceRemoteInterface* fundServiceRemoteInterface;
  TransferService(
      TransferRepositoryInterface* transfer_Repository_Interface_,
      TransferQueryInterface* transfer_Query_Interface,
      UserServiceInterface* userService_Interface,
      FundServiceRemoteInterface* fund_Service_Remote_Interface)
      : transferRepositoryInterface(transfer_Repository_Interface_),
        transferQueryInterface(transfer_Query_Interface),
        userServiceInterface(userService_Interface),
        fundServiceRemoteInterface(fund_Service_Remote_Interface) {}

  void RefundFinish(int order_id, Transfer& transfer) const {
    transfer.RefundFinshed();
    transferRepositoryInterface->UpdateTransferStatus(transfer);
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
        "转账已退回",
        order_id,
        Payee_Increased_DTO(
            order_id,
            transfer.GetPayerAccountId(),
            transfer.GetPayeeAccountId(),
            transfer.GetAmount())
            .Serialize()));
  }

  void PayeeIncreased(int id, Transfer& transfer) const {
    transfer.PayeeFundIncreased();
    transferRepositoryInterface->UpdateTransferStatus(transfer);
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
        "转账已到账",
        id,
        Payee_Increased_DTO(
            id, transfer.GetPayerAccountId(), transfer.GetPayeeAccountId(), transfer.GetAmount())
            .Serialize()));
  }

  static TransferService* transfer_Service_;

 public:
  ~TransferService() { TransferService::transfer_Service_ = nullptr; }

  static TransferService* BuildInstance(
      TransferRepositoryInterface* transfer_Repository_Interface,
      TransferQueryInterface* transfer_Query_Interface,
      UserServiceInterface* user_Service_Interface,
      FundServiceRemoteInterface* fund_Service_Remote_Interface) {
    if (TransferService::transfer_Service_ == nullptr) {
      TransferService::transfer_Service_ = new TransferService(
          transfer_Repository_Interface,
          transfer_Query_Interface,
          user_Service_Interface,
          fund_Service_Remote_Interface);
    }
    return TransferService::transfer_Service_;
  }

  static TransferService* GetInstance() {
    if (TransferService::transfer_Service_ == nullptr) {
      throw "单例未创建";
    }
    return TransferService::transfer_Service_;
  }

  static void DestroySingleton() {
    if (TransferService::transfer_Service_ != nullptr) delete TransferService::transfer_Service_;
  }

  virtual int ApplyTransfer(std::string payer, std::string payee, float amount) override {
    TransferUser tansfer_payer = TransferUser(payer, userServiceInterface->IsFrozen(payer));
    TransferUser tansfer_payee = TransferUser(payee, userServiceInterface->IsFrozen(payee));
    bool locked = fundServiceRemoteInterface->LockAmount(payer, amount);
    if (!locked) {
      throw Exception("可用金额不足，转账创建失败");
    }
    Transfer transfer = Transfer::CreateNew(tansfer_payer, tansfer_payee, amount);
    transferRepositoryInterface->AddTransfer(transfer);
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
        "转账已创建",
        transfer.GetOrderNo(),
        Refund_Created_DTO(transfer.GetOrderNo(), payer, amount).Serialize()));
    return transfer.GetOrderNo();
  }

  virtual void NotifyFundIncreased(int order_no, std::string payee_account) override {
    Transfer transfer = transferRepositoryInterface->GetExistedTransfer(order_no);
    if (payee_account == transfer.GetPayeeAccountId()) {
      PayeeIncreased(order_no, transfer);
    }
    if (payee_account == transfer.GetPayerAccountId()) {
      RefundFinish(order_no, transfer);
    }
  }

  virtual void NotifyCancel(int order_no, Exception cancel_reason) override {
    Transfer transfer = transferRepositoryInterface->GetExistedTransfer(order_no);
    transfer.Cancel(cancel_reason);
    transferRepositoryInterface->UpdateTransferStatus(transfer);
  }

  virtual void NotifyApplyRefund(int order_no, Exception refund_reason) override {
    Transfer transfer = transferRepositoryInterface->GetExistedTransfer(order_no);
    transfer.ApplyRefund(refund_reason);
    transferRepositoryInterface->UpdateTransferStatus(transfer);
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
        "转账退款中",
        order_no,
        Refund_DTO(order_no, transfer.GetPayerAccountId(), transfer.GetAmount()).Serialize()));
  }

  virtual void NotifyPayerFundDeducted(int order_no) override {
    Transfer transfer = transferRepositoryInterface->GetExistedTransfer(order_no);
    transfer.PayerFundDeducted();
    transferRepositoryInterface->UpdateTransferStatus(transfer);
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent(
        "转账已出账",
        order_no,
        Payer_Deducted_DTO(order_no, transfer.GetPayeeAccountId(), transfer.GetAmount())
            .Serialize()));
  }

  virtual boost::optional<TransferDTO> GetTransfer(int order_no) override {
    boost::optional<Transfer> transfer_optinal = transferQueryInterface->Get_Transfer(order_no);
    if (transfer_optinal.has_value()) {
      Transfer transfer = transfer_optinal.value();
      return TransferDTO(
          transfer.GetOrderNo(),
          transfer.GetPayerAccountId(),
          transfer.GetPayeeAccountId(),
          transfer.GetAmount(),
          transfer.GetStatus());
    }
    return boost::none;
  }
};

#endif  // ARGS_TransferService_H
