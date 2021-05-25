#ifndef TRANSFER_主适配器请求测试环境_H
#define TRANSFER_主适配器请求测试环境_H
#include "gtest/gtest.h"
#include "../../../src/UserBC/FrontendAdapters/UserRequireMapping.h"
#include "../../../src/FrameworkComponents/LocalRequestionFilters/RequestionConfigure.h"
#include "UserServiceMock.h"
#include "../../../src/UserBC/FrontendAdapters/UserHttpService.h"
class TransferFrontendEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::获取单例()->注册请求处理器("UserRequireMapping", UserRequireMapping::构建单例(UserServiceMock::构造单例()));
        NamingServiceManager::获取单例()->注册服务<UserHttpService *>("UserHttpService", UserHttpService::构建单例(RequireInterceptor::获取单例()));
    }
    virtual void TearDown() {
        RequestionConfigure::销毁单例();
        UserRequireMapping::销毁单例();
        UserServiceMock::销毁单例();
        UserHttpService::销毁单例();
        NamingServiceManager::销毁单例();
    }
};
#endif //TRANSFER_主适配器请求测试环境_H
