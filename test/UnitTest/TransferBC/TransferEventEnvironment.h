#ifndef TRANSFER_主适配器事件测试环境_H
#define TRANSFER_主适配器事件测试环境_H
#include "gtest/gtest.h"
#include "../../../src/TransferBC/FrontendAdapters/TransferEventMonitor.h"
#include "../../../src/GlobalBusinessDependency/ServiceInterfaces/TransferServiceInterface.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../../src/FrameworkComponents/DomainEvent/EventMonitor.h"
#include "TansferServiceMock.h"

class TransferEventEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        NamingServiceManager::获取单例()->注册服务("TransferService", (TransferServiceInterface *) TansferServiceMock::获取单例());
        NamingServiceManager::获取单例()->注册服务("TransferEventMonitor", (EventMonitor *) TransferEventMonitor::构建单例(TansferServiceMock::获取单例()));
        PublishSubscribeService::构建单例()->订阅("增资已成功", "TransferEventMonitor");
        PublishSubscribeService::构建单例()->订阅("增资已失败", "TransferEventMonitor");
        PublishSubscribeService::构建单例()->订阅("扣减已成功", "TransferEventMonitor");
        PublishSubscribeService::构建单例()->订阅("扣减已失败", "TransferEventMonitor");
    }
    virtual void TearDown() {
        delete NamingServiceManager::获取单例()->注销服务<EventMonitor *>("TransferEventMonitor").value();
        delete NamingServiceManager::获取单例()->注销服务<TransferServiceInterface *>("TransferService").value();
        NamingServiceManager::销毁单例();
        PublishSubscribeService::销毁单例();
    }
};
#endif //TRANSFER_主适配器事件测试环境_H
