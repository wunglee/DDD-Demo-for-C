#ifndef TRANSFER_TransferEventMonitor_H
#define TRANSFER_TransferEventMonitor_H
#include "../../../framework_components/domain_event/event_monitor.h"
#include "../../../framework_components/requestion_filters/require_interceptor.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_dto.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_service_interface.h"
//从事件队列中取出事件进行处理
class TransferEventMonitor : public EventMonitor {
 private:
  RequireInterceptor* require_interceptor_ = nullptr;
  static TransferEventMonitor* transferEventMonitor_;
  TransferEventMonitor(RequireInterceptor* requireInterceptor)
      : require_interceptor_(requireInterceptor) {}

 public:
  virtual ~TransferEventMonitor() { TransferEventMonitor::transferEventMonitor_ = nullptr; }
  static TransferEventMonitor* BuildInstance(RequireInterceptor* requireInterceptor) {
    if (TransferEventMonitor::transferEventMonitor_ == nullptr) {
      TransferEventMonitor::transferEventMonitor_ = new TransferEventMonitor(requireInterceptor);
    }
    return TransferEventMonitor::transferEventMonitor_;
  }
  static TransferEventMonitor* GetInstance() {
    if (TransferEventMonitor::transferEventMonitor_ == nullptr) {
      throw "单例未构建";
    }
    return TransferEventMonitor::transferEventMonitor_;
  }
  static void DestroyInstance() {
    if (TransferEventMonitor::transferEventMonitor_ != nullptr) {
      delete TransferEventMonitor::transferEventMonitor_;
    }
  }
  // TODO:需要重构，太多if
  virtual void Handle(const DomainEvent domainEvent) override {
    std::string eventName = domainEvent.Get_Name();
    std::string eventContent = domainEvent.Get_Content();
    int id = domainEvent.Get_Transaction_Id();
    if (eventName == "扣减已成功") {
      Require require(std::to_string(id), "TransferRequireMapping", "NotifyPayerFundDeducted", id);
      require_interceptor_->Commit(require);
    }
    if (eventName == "扣减已失败") {
      DecreaseFailDTO subAmountFailDTO = DecreaseFailDTO::Unserialize(eventContent);
      Require require(
          std::to_string(id), "TransferRequireMapping", "NotifyCancel", subAmountFailDTO);
      require_interceptor_->Commit(require);
    }
    if (eventName == "增资已成功") {
      IncreaseSuccessDTO addAmountSuccessDTO = IncreaseSuccessDTO::Unserialize(eventContent);
      Require require(
          std::to_string(id), "TransferRequireMapping", "NotifyFundIncreased", addAmountSuccessDTO);
      require_interceptor_->Commit(require);
    }
    if (eventName == "增资已失败") {
      IncreaseFailDTO addAmountFailDTO = IncreaseFailDTO::Unserialize(eventContent);
      Require require(
          std::to_string(id), "TransferRequireMapping", "NotifyApplyRefund", addAmountFailDTO);
      require_interceptor_->Commit(require);
    }
  };
};

#endif  // TRANSFER_TransferEventMonitor_H
