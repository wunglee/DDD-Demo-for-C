#ifndef TRANSFER_主适配器事件测试环境_H
#define TRANSFER_主适配器事件测试环境_H
#include "gtest/gtest.h"
#include "../../../src/FundBC/FrontendAdapters/FundEventMapping.h"
#include "../../../src/GlobalBusinessDependency/ServiceInterfaces/FundServiceInterface.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../../src/FrameworkComponents/DomainEvent/PublishSubscribeService.h"
#include "../../../src/FrameworkComponents/DomainEvent/EventMonitor.h"
#include "FundServiceMock.h"

class FundFrontendEnvironment : public ::testing::Test {
public:
    FundServiceMock* 资金帐户服务模拟_=FundServiceMock::获取单例();
    virtual void SetUp() {
        NamingServiceManager::获取单例()->注册服务("FundService", (FundServiceInterface *) 资金帐户服务模拟_);
        NamingServiceManager::获取单例()->注册服务("FundEventMapping", (EventMonitor *) FundEventMapping::构建单例(FundServiceMock::获取单例()));
        PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
        PublishSubscribeService::构建单例()->订阅("用户已创建", "FundEventMapping");
        PublishSubscribeService::构建单例()->订阅("转账已出账", "FundEventMapping");
        PublishSubscribeService::构建单例()->订阅("转账退款中", "FundEventMapping");
    }
    virtual void TearDown() {
        delete NamingServiceManager::获取单例()->注销服务<EventMonitor *>("FundEventMapping").value();
        delete NamingServiceManager::获取单例()->注销服务<FundServiceInterface *>("FundService").value();
        delete FundServiceMock::获取单例();
        PublishSubscribeService::销毁单例();
    }
};
#endif //TRANSFER_主适配器事件测试环境_H
