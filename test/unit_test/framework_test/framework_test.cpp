#include "gtest/gtest.h"
#include "domain_event_test_environment.h"
#include "../../../src/bc/fund/backend_adapters/fund_menory_dao.h"
#include "../../../src/bc/user/backend_adapters/user_menory_dao.h"
#include "../../../src/framework_components/requestion_filters/require_interceptor.h"
#include "require_test_environment1.h"
#include "require_test_environment2.h"

TEST(NamingServiceManager,register_and_discover_service){
    NamingServiceManager::GetInstance()->Add_Service("EventMonitorMock",
                                                       (EventMonitor *) new EventMonitorMock());
    boost::optional<EventMonitor*> eventMonitor_optional= NamingServiceManager::GetInstance()->Find_Service<EventMonitor *>(
            "EventMonitorMock");
    ASSERT_EQ(eventMonitor_optional.has_value(), true);
    delete NamingServiceManager::GetInstance()->Remove_Service<EventMonitor *>("EventMonitorMock").value();
    NamingServiceManager::Destroy_Singleton();
}

TEST_F(DomainEventTestEnvironment, publish_event){
    PublishSubscribeService::BuildInstance()->Publish(DomainEvent("转账已创建", 0, ""));
    EventMonitor* eventMonitor= NamingServiceManager::GetInstance()->Find_Service<EventMonitor *>("EventMonitorMock").value();
    EventMonitorMock *eventMonitorMock =dynamic_cast<EventMonitorMock*>(eventMonitor);
    ASSERT_EQ(eventMonitorMock->getResult(), true);
}
void test_commit(){
    Require require(
            "1",
           "RequireMappingMock",
           "function_name_",
           boost::any("parameters_"),
            {"拦截1","拦截2"});
    Response response=RequireInterceptor::GetInstance()->Commit(require);
    ASSERT_EQ(boost::any_cast<bool>(response.value),true);
}
TEST_F(RequireTestEnvironment1, test_commit){
    test_commit();
}
TEST_F(RequireTestEnvironment2, test_interceptor){
    test_commit();
    ASSERT_EQ(requireFilterMock1->beforeExecute, true);
    ASSERT_EQ(requireFilterMock1->afterExecute, true);
    ASSERT_EQ(requireFilterMock2->beforeExecute, true);
    ASSERT_EQ(requireFilterMock2->afterExecute, true);
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}