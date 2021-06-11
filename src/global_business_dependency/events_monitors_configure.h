#ifndef TRANSFER_EventsMonitorsConfigure_H
#define TRANSFER_EventsMonitorsConfigure_H
#include "../bc/transfer/frontend_adapters/transfer_event_monitor.h"
#include "../framework_components/naming_service/naming_service_manager.h"
#include "../../test/integration_test/fund_service_factory_for_integration.h"
#include "../../test/integration_test/transfer_service_factory_for_integration.h"

class EventsMonitorsConfigure {
public:
    static void RegisterEventMappings(){
        NamingServiceManager::GetInstance()->Add_Service("FundEventMonitor",
                                                           (EventMonitor *) FundEventMonitor::BuildInstance(
                                                                   RequireInterceptor::BuildInstance()));
        NamingServiceManager::GetInstance()->Add_Service("TransferEventMonitor",
                                                           (EventMonitor *) TransferEventMonitor::BuildInstance(
                                                                   RequireInterceptor::BuildInstance()));
   }
   static void UnRegisterEventMappings(){
       NamingServiceManager::GetInstance()->Remove_Service<EventMonitor *>("FundEventMonitor");
       NamingServiceManager::GetInstance()->Remove_Service<EventMonitor *>("TransferEventMonitor");
       FundEventMonitor::DestroyInstance();
       TransferEventMonitor::DestroyInstance();
       RequireInterceptor::Destroy_Singleton();
   }
};


#endif //TRANSFER_EventsMonitorsConfigure_H
