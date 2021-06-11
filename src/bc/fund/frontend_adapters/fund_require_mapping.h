#ifndef DDD_DEMO_FOR_C_FUND_REQUIRE_MAPPING_H
#define DDD_DEMO_FOR_C_FUND_REQUIRE_MAPPING_H

#include "../../../global_business_dependency/service_interfaces/user/user_dto.h"

#include "../../../global_business_dependency/service_interfaces/fund/fund_dto.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_dto.h"
#include "../application/fund_service.h"
class FundRequireMapping : public RequireMapping {
 private:
  FundServiceLocalInterface* fund_service_local_interface_;  // 资金服务接口
  static FundRequireMapping* fund_require_mapping_;          // 资金请求处理器
  FundRequireMapping(FundServiceLocalInterface* fund_service_local_interface_)
      : fund_service_local_interface_(fund_service_local_interface_) {}

 public:
  virtual ~FundRequireMapping() { FundRequireMapping::fund_require_mapping_ = nullptr; }

  static FundRequireMapping* BuildInstance(
      FundServiceLocalInterface* fund_service_local_interface) {
    if (FundRequireMapping::fund_require_mapping_ == nullptr) {
      FundRequireMapping::fund_require_mapping_ =
          new FundRequireMapping(fund_service_local_interface);
    }
    return FundRequireMapping::fund_require_mapping_;
  }

  static FundRequireMapping* GetInstance() {
    if (FundRequireMapping::fund_require_mapping_ == nullptr) {
      throw "单例未构建";
    }
    return FundRequireMapping::fund_require_mapping_;
  }

  static void DestroyInstance() {
    if (FundRequireMapping::fund_require_mapping_ != nullptr) {
      delete FundRequireMapping::fund_require_mapping_;
    }
  }

  virtual Response handle(std::string func, const boost::any& parameter) override {
    Response response;
    try {
      if (func == "Decrease") {
        Refund_Created_DTO refund_Created_DTO = boost::any_cast<Refund_Created_DTO>(parameter);
        fund_service_local_interface_->UnLockAmount(
            refund_Created_DTO.payer_account_, refund_Created_DTO.amount_);
        fund_service_local_interface_->Decrease(
            refund_Created_DTO.order_no_,
            refund_Created_DTO.payer_account_,
            refund_Created_DTO.amount_);
      }
      if (func == "AddFundAccount") {
        UserCreatedDTO user_created_dto = boost::any_cast<UserCreatedDTO>(parameter);
        fund_service_local_interface_->AddFundAccount(user_created_dto.account_id_);
      }
      if (func == "add_amount_to_payee") {
        Payer_Deducted_DTO payer_Deducted_DTO = boost::any_cast<Payer_Deducted_DTO>(parameter);
        fund_service_local_interface_->Increase(
            payer_Deducted_DTO.order_no_,
            payer_Deducted_DTO.payee_account_,
            payer_Deducted_DTO.amount_);
      }
      if (func == "add_amount_to_payer") {
        Refund_DTO refund_DTO = boost::any_cast<Refund_DTO>(parameter);
        fund_service_local_interface_->Increase(
            refund_DTO.order_no_, refund_DTO.payer_account_, refund_DTO.amount_);
      }
      if (func == "lock_amount") {
        LockAmountDTO lock_Amount_DTO = boost::any_cast<LockAmountDTO>(parameter);
        response.value = fund_service_local_interface_->LockAmount(
            lock_Amount_DTO.account_id_, lock_Amount_DTO.amount_);
      }
    } catch (Exception e) {
      response.exception = std::make_shared<Exception>(e);
    }
    return response;
  }
};

#endif  // DDD_DEMO_FOR_C_FUND_REQUIRE_MAPPING_H
