#ifndef TRANSFER_事件处理器管理_H
#define TRANSFER_事件处理器管理_H
#include "../TransferBC/FrontendAdapters/TransferEventMonitor.h"
#include "../FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../product/FundServiceFactory.h"
#include "../../product/TransferServiceFactory.h"

class EventsMonitorsConfigure {
public:
    static void 注册事件处理器(){
        NamingServiceManager::获取单例()->注册服务("FundEventMapping", (EventMonitor *) FundEventMapping::构建单例(FundServiceFactory::获取单例()));
        NamingServiceManager::获取单例()->注册服务("TransferEventMonitor", (EventMonitor *) TransferEventMonitor::构建单例(TransferServiceFactory::获取单例()));
   }
   static void 注销事件处理器(){
       NamingServiceManager::获取单例()->注销服务<EventMonitor *>("FundEventMapping");
       NamingServiceManager::获取单例()->注销服务<EventMonitor *>("TransferEventMonitor");
       FundEventMapping::销毁单例();
       TransferEventMonitor::销毁单例();
   }
};


#endif //TRANSFER_事件处理器管理_H
