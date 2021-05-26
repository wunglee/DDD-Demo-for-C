#ifndef TRANSFER_请求总线测试环境2_H
#define TRANSFER_请求总线测试环境2_H
#include "gtest/gtest.h"
#include "../../src/FrameworkComponents/RequestionFilters/RequireInterceptor.h"
#include "../../src/FrameworkComponents/RequestionFilters/RequiresQueuePoolInterface.h"
#include "../../src/FrameworkComponents/RequestionFilters/RequiresQueuePool.h"
#include "../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "RequireMappingMock.h"
#include "RequireFilterMock1.h"
#include "RequireFilterMock2.h"
class RequireTestEnvironment2: public ::testing::Test {
public:
    RequireMapping * 模拟处理器_= nullptr;
    请求过滤器模拟1 * 请求过滤器模拟1_= nullptr;
    请求过滤器模拟2 * 请求过滤器模拟2_= nullptr;
    std::list<Filter*> 请求过滤器列表;
    virtual void SetUp() {
        NamingServiceManager::获取单例()->注册服务<RequiresQueuePoolInterface *>("RequiresQueuePool", RequiresQueuePool::构建单例());
        模拟处理器_=new RequireMappingMock();
        请求过滤器模拟1_=new 请求过滤器模拟1("拦截1");
        请求过滤器模拟2_=new 请求过滤器模拟2("拦截2");
        请求过滤器列表.assign({请求过滤器模拟1_,请求过滤器模拟2_});
        RequireMappingsManager* 请求处理器管理器_=RequireMappingsManager::构建单例(请求过滤器列表);
        请求处理器管理器_->注册请求处理器("RequireMappingMock", 模拟处理器_);
        NamingServiceManager::获取单例()->注册服务<RequireMappingsManager *>("RequireMappingsManager", 请求处理器管理器_);
     }

    virtual void TearDown() {
        RequiresQueuePool::销毁单例();
        RequireMappingsManager::销毁单例();
        delete 模拟处理器_;
        RequireInterceptor::销毁单例();
        请求过滤器列表.clear();
        delete 请求过滤器模拟1_;
        delete 请求过滤器模拟2_;
        NamingServiceManager::销毁单例();
    }
};


#endif //TRANSFER_请求总线测试环境2_H
