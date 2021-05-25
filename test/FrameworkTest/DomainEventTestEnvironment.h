#ifndef TRANSFER_事件总线测试环境_H
#define TRANSFER_事件总线测试环境_H
#include "gtest/gtest.h"
#include "EventMonitorMock.h"
#include "../../src/FrameworkComponents/DomainEvent/PublishSubscribeService.h"
#include "../../src/FrameworkComponents/NamingService/NamingServiceManager.h"

class DomainEventTestEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        NamingServiceManager::获取单例()->注册服务("EventMonitorMock", (EventMonitor *) new EventMonitorMock());
        PublishSubscribeService::构建单例()->订阅("转账已创建", "EventMonitorMock");
    }
    virtual void TearDown() {
        delete NamingServiceManager::获取单例()->注销服务<EventMonitor *>("EventMonitorMock").value();
        PublishSubscribeService::销毁单例();
        NamingServiceManager::销毁单例();
    }
};


#endif //TRANSFER_事件总线测试环境_H
