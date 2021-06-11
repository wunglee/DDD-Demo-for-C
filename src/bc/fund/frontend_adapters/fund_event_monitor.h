#ifndef TRANSFER_FundEventMapping_H
#define TRANSFER_FundEventMapping_H
#include "../../../framework_components/domain_event/event_monitor.h"
#include "../../../framework_components/requestion_filters/require_interceptor.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_service_local_interface.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_dto.h"
#include "../../user/frontend_adapters/user_require_mapping.h"

//从事件队列中取出事件进行处理
class FundEventMonitor : public EventMonitor {
 private:
  RequireInterceptor* require_interceptor_ = nullptr;
  static FundEventMonitor* fund_event_mapping_;
  FundEventMonitor(RequireInterceptor* require_interceptor)
      : require_interceptor_(require_interceptor) {}

 public:
  ~FundEventMonitor() { FundEventMonitor::fund_event_mapping_ = nullptr; }
  static FundEventMonitor* BuildInstance(RequireInterceptor* require_interceptor) {
    assert(require_interceptor != nullptr);
    if (FundEventMonitor::fund_event_mapping_ == nullptr) {
        FundEventMonitor::fund_event_mapping_ = new FundEventMonitor(require_interceptor);
    }
    return FundEventMonitor::fund_event_mapping_;
  }
  static FundEventMonitor* GetInstance() {
    if (FundEventMonitor::fund_event_mapping_ == nullptr) {
      throw "单例未创建";
    }
    return FundEventMonitor::fund_event_mapping_;
  }
  static void DestroyInstance() {
    if (FundEventMonitor::fund_event_mapping_ != nullptr) {
      delete FundEventMonitor::fund_event_mapping_;
    }
  }
  // TODO:还需要重构
  void Handle(const DomainEvent domainEvent) {
    std::string eventContent;
    std::string event_name = domainEvent.Get_Name();
    if (event_name == "转账已创建") {
      eventContent = domainEvent.Get_Content();
      Refund_Created_DTO refund_created_dto = Refund_Created_DTO::Unserialize(eventContent);
      Require require("1", "FundRequireMapping",
                      "Decrease", refund_created_dto);
      require_interceptor_->Commit(require);
    }
    if (event_name == "用户已创建") {
      eventContent = domainEvent.Get_Content();
      UserCreatedDTO content = UserCreatedDTO::Unserialize(eventContent);
      Require require("1", "FundRequireMapping", "AddFundAccount", content);
      require_interceptor_->Commit(require);
    }
    if (event_name == "转账已出账") {
      eventContent = domainEvent.Get_Content();
      Payer_Deducted_DTO payer_Deducted_DTO = Payer_Deducted_DTO::Unserialize(eventContent);
      Require require("1", "FundRequireMapping", "add_amount_to_payee", payer_Deducted_DTO);
      require_interceptor_->Commit(require);
    }
    if (event_name == "转账退款中") {
      eventContent = domainEvent.Get_Content();
      Refund_DTO refund_DTO = Refund_DTO::Unserialize(eventContent);
      Require require("1", "FundRequireMapping", "add_amount_to_payer", refund_DTO);
      require_interceptor_->Commit(require);
    }
  };
};
#endif  // TRANSFER_FundEventMapping_H
