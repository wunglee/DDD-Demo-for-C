#ifndef TRANSFER_事件处理器管理_H
#define TRANSFER_事件处理器管理_H
#include "../../product/FundServiceFactory.h"
#include "../../product/TransferServiceFactory.h"
#include "../TransferBC/frontend_adapters/TransferEventMonitor.h"
#include "../framework_components/NamingService/NamingServiceManager.h"

class EventsMonitorsConfigure {
 public:
  static void 注册事件处理器() {
    NamingServiceManager::GetInstance()->注册服务(
        "FundEventMapping",
        (EventMonitor*)FundEventMapping::BuildInstance(FundServiceFactory::GetInstance()));
    NamingServiceManager::GetInstance()->注册服务(
        "TransferEventMonitor",
        (EventMonitor*)TransferEventMonitor::BuildInstance(TransferServiceFactory::GetInstance()));
  }
  static void 注销事件处理器() {
    NamingServiceManager::GetInstance()->注销服务<EventMonitor*>("FundEventMapping");
    NamingServiceManager::GetInstance()->注销服务<EventMonitor*>("TransferEventMonitor");
    FundEventMapping::销毁单例();
    TransferEventMonitor::销毁单例();
  }
};

#endif  // TRANSFER_事件处理器管理_H
