#ifndef TRANSFER_FundFrontendEnvironmentForEvent_H
#define TRANSFER_FundFrontendEnvironmentForEvent_H
#include "gtest/gtest.h"
#include "../../../../src/bc/fund/frontend_adapters/fund_event_monitor.h"
#include "../../../../src/global_business_dependency/service_interfaces/fund/fund_service_local_interface.h"
#include "../../../../src/framework_components/naming_service/naming_service_manager.h"
#include "../../../../src/framework_components/domain_event/publish_subscribe_service.h"
#include "../../../../src/framework_components/domain_event/event_monitor.h"
#include "fund_service_mock.h"
#include "../../../../src/framework_components/requestion_filters/requestion_configure.h"
#include "../../../../src/bc/fund/frontend_adapters/fund_require_mapping.h"

class FundFrontendEnvironmentForEvent : public ::testing::Test {
public:
    FundServiceMock* fundServiceMock=FundServiceMock::GetInstance();
    virtual void SetUp() {
        NamingServiceManager::GetInstance()->Add_Service("FundService", (FundServiceLocalInterface *) fundServiceMock);
        NamingServiceManager::GetInstance()->Add_Service("FundEventMonitor",
                                                           (EventMonitor *) FundEventMonitor::BuildInstance(
                                                                   RequireInterceptor::BuildInstance()));
        PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
        PublishSubscribeService::GetInstance()->Subscribe("用户已创建", "FundEventMonitor");
        PublishSubscribeService::GetInstance()->Subscribe("转账已出账", "FundEventMonitor");
        PublishSubscribeService::GetInstance()->Subscribe("转账退款中", "FundEventMonitor");
        RequestionConfigure::GetInstance()->Add_Require_Mapping("FundRequireMapping",
                                                         FundRequireMapping::BuildInstance(fundServiceMock));

    }
    virtual void TearDown() {
        delete NamingServiceManager::GetInstance()->Remove_Service<EventMonitor *>("FundEventMonitor").value();
        delete NamingServiceManager::GetInstance()->Remove_Service<FundServiceLocalInterface *>("FundService").value();
        FundServiceMock::DestroyInstance();
        RequireInterceptor::Destroy_Singleton();
        PublishSubscribeService::DestoryInstance();
        RequestionConfigure::DestroyInstance();
        FundRequireMapping::DestroyInstance();
    }
};
#endif //TRANSFER_FundFrontendEnvironmentForEvent_H
