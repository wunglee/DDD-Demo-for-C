#ifndef TRANSFER_转账流程测试环境_H
#define TRANSFER_转账流程测试环境_H
#include "../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "gtest/gtest.h"
#include "../../product/FundServiceFactory.h"
#include "../../product/UserServiceFactory.h"
#include "../../src/UserBC/FrontendAdapters/UserHttpService.h"
#include "../../src/UserBC/FrontendAdapters/UserRequireMapping.h"
#include "../../product/TransferServiceFactory.h"
#include "../UnitTest/UserBC/UserServiceMock.h"
#include "../../src/GlobalBusinessDependency/EventsMonitorsConfigure.h"
#include "../../src/FrameworkComponents/RequestionFilters/RequestionConfigure.h"
#include "../../src/GlobalBusinessDependency/ServiceInterfaces/UserHttpClient.h"
#include "../CommonTestFuntions.h"


class RequireFlowTestEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::获取单例()->注册请求处理器("UserRequireMapping", UserRequireMapping::构建单例(UserServiceFactory::获取单例()));
        NamingServiceManager::获取单例()->注册服务<UserHttpService *>("用户HTTP服务", UserHttpService::构建单例(RequireInterceptor::获取单例()));
        EventsMonitorsConfigure::注册事件处理器();
        初始化资金帐户(UserHttpClient::获取单例());
    }
    virtual void TearDown() {
        UserHttpClient::销毁单例();
        UserHttpService::销毁单例();

        FundServiceFactory::销毁单例();
        TransferServiceFactory::销毁单例();
        UserServiceFactory::销毁单例();

        EventsMonitorsConfigure::注销事件处理器();
        PublishSubscribeService::销毁单例();
        RequestionConfigure::销毁单例();

        UserRequireMapping::销毁单例();
        NamingServiceManager::销毁单例();
    }




};
#endif //TRANSFER_转账流程测试环境_H
