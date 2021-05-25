#ifndef TRANSFER_请求总线测试环境_H
#define TRANSFER_请求总线测试环境_H
#include "gtest/gtest.h"
#include "../../src/FrameworkComponents/LocalRequestionFilters/RequireAccepter.h"
#include "../../src/FrameworkComponents/LocalRequestionFilters/RequiresQueuePoolInterface.h"
#include "../../src/FrameworkComponents/LocalRequestionFilters/RequiresQueuePool.h"
#include "../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "RequireMappingMock.h"
#include "RequireFilterMock1.h"
#include "RequireFilterMock2.h"
class RequireTestEnvironment1: public ::testing::Test {
public:
    RequireMapping * 请求处理器_= nullptr;
    virtual void SetUp() {
        NamingServiceManager::获取单例()->注册服务<RequiresQueuePoolInterface *>("RequiresQueuePool", RequiresQueuePool::构建单例());
        请求处理器_=new RequireMappingMock();
        RequireMappingsManager::构建单例()->注册请求处理器("RequireMappingMock", 请求处理器_);
        NamingServiceManager::获取单例()->注册服务<RequireMappingsManager *>("RequireMappingsManager", RequireMappingsManager::构建单例());
        NamingServiceManager::获取单例()->注册服务<RequireAccepter *>("RequireAccepter", RequireAccepter::获取单例());
     }

    virtual void TearDown() {
        RequiresQueuePool::销毁单例();
        NamingServiceManager::销毁单例();
        RequireMappingsManager::销毁单例();
        RequireAccepter::销毁单例();
        delete 请求处理器_;
    }
};


#endif //TRANSFER_请求总线测试环境_H
