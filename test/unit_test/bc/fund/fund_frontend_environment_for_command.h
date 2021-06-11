#ifndef DDD_DEMO_FOR_C_FUND_FRONTEND_ENVIRONMENT_FOR_COMMAND_H
#define DDD_DEMO_FOR_C_FUND_FRONTEND_ENVIRONMENT_FOR_COMMAND_H
#include "gtest/gtest.h"
#include "../../../../src/global_business_dependency/service_interfaces/fund/fund_service_local_interface.h"
#include "../../../../src/framework_components/naming_service/naming_service_manager.h"
#include "../../../../src/framework_components/domain_event/event_monitor.h"
#include "fund_service_mock.h"
#include "../../../../src/framework_components/requestion_filters/requestion_configure.h"
#include "../../../../src/bc/fund/frontend_adapters/fund_require_mapping.h"
class FundFrontendEnvironmentForCommand : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::GetInstance()->Add_Require_Mapping("FundRequireMapping", FundRequireMapping::BuildInstance(FundServiceMock::GetInstance()));
        NamingServiceManager::GetInstance()->Add_Service("FundHttpService",
                                                         FundHttpService::BuildInstance(RequireInterceptor::GetInstance()));
    }
    virtual void TearDown() {
        NamingServiceManager::GetInstance()->Remove_Service<FundHttpService*>("FundHttpService");
        FundHttpService::Destroy_Singleton();
        FundServiceMock::DestroyInstance();
        RequireInterceptor::Destroy_Singleton();
        RequestionConfigure::DestroyInstance();
        FundRequireMapping::DestroyInstance();
    }
};


#endif //DDD_DEMO_FOR_C_FUND_FRONTEND_ENVIRONMENT_FOR_COMMAND_H
