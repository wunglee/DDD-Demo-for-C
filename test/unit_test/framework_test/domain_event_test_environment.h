#ifndef TRANSFER_DomainEventTestEnvironment_H
#define TRANSFER_DomainEventTestEnvironment_H
#include "gtest/gtest.h"
#include "event_monitor_mock.h"
#include "../../../src/framework_components/domain_event/publish_subscribe_service.h"
#include "../../../src/framework_components/naming_service/naming_service_manager.h"

class DomainEventTestEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        NamingServiceManager::GetInstance()->Add_Service("EventMonitorMock",
                                                           (EventMonitor *) new EventMonitorMock());
        PublishSubscribeService::BuildInstance()->Subscribe("转账已创建", "EventMonitorMock");
    }
    virtual void TearDown() {
        delete NamingServiceManager::GetInstance()->Remove_Service<EventMonitor *>("EventMonitorMock").value();
        PublishSubscribeService::DestoryInstance();
        NamingServiceManager::Destroy_Singleton();
    }
};


#endif //TRANSFER_DomainEventTestEnvironment_H
