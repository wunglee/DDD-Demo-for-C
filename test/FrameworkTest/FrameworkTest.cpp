#include "gtest/gtest.h"
#include "DomainEventTestEnvironment.h"
#include "../../src/FundBC/BackendAdapters/FundDAO.h"
#include "../../src/UserBC/BackendAdapters/UserDAO.h"
#include "../../src/FrameworkComponents/LocalRequestionFilters/RequireAccepter.h"
#include "RequireTestEnvironment1.h"
#include "RequireTestEnvironment2.h"

TEST(服务注册与发现,注册与查找服务){
    NamingServiceManager::获取单例()->注册服务("EventMonitorMock", (EventMonitor *) new EventMonitorMock());
    boost::optional<EventMonitor*> 事件监听器_= NamingServiceManager::获取单例()->查找服务<EventMonitor *>("EventMonitorMock");
    ASSERT_EQ(事件监听器_.has_value(),true);
    delete NamingServiceManager::获取单例()->注销服务<EventMonitor *>("EventMonitorMock").value();
    NamingServiceManager::销毁单例();
}

TEST_F(DomainEventTestEnvironment, 测试){
    PublishSubscribeService::构建单例()->发布(DomainEvent("转账已创建", 0, ""));
    EventMonitor* 事件监听器_= NamingServiceManager::获取单例()->查找服务<EventMonitor *>("EventMonitorMock").value();
    EventMonitorMock *事件监听器模拟_ =dynamic_cast<EventMonitorMock*>(事件监听器_);
    ASSERT_EQ(事件监听器模拟_->获取处理结果(), true);
}
void 测试提交请求(){
    bool 回调成功=false;
    std::function<void(Response&)> 回调函数=[&](Response& 处理结果_) mutable{
        if(处理结果_.异常_==nullptr){
            回调成功=true;
        }
    };
    Require 请求_(
            "1",
           "RequireMappingMock",
           "方法名",
           boost::any("参数"),
            &回调函数,
            {"拦截1","拦截2"});
    RequireAccepter::获取单例()->提交请求(请求_);
    ASSERT_EQ(回调成功, true);
}
TEST_F(RequireTestEnvironment1, 提交请求){
    测试提交请求();
}
TEST_F(RequireTestEnvironment2, 拦截请求){
    测试提交请求();
    ASSERT_EQ(请求拦截器模拟1_->执行前调用, true);
    ASSERT_EQ(请求拦截器模拟1_->执行后调用, true);
    ASSERT_EQ(请求拦截器模拟2_->执行前调用, true);
    ASSERT_EQ(请求拦截器模拟2_->执行后调用, true);
}
