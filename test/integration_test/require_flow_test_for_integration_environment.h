#ifndef TRANSFER_RequireFlowTestEnvironment_H
#define TRANSFER_RequireFlowTestEnvironment_H
#include "gtest/gtest.h"

#include "fund_service_factory_for_integration.h"
#include "transfer_service_factory_for_integration.h"
#include "user_service_factory_for_integration.h"
#include "../../src/bc/fund/frontend_adapters/fund_require_mapping.h"
#include "../../src/bc/transfer/frontend_adapters/transfer_require_mapping.h"
#include "../../src/bc/user/frontend_adapters/user_http_service.h"
#include "../../src/bc/user/frontend_adapters/user_require_mapping.h"
#include "../../src/framework_components/naming_service/naming_service_manager.h"
#include "../../src/framework_components/requestion_filters/requestion_configure.h"
#include "../../src/global_business_dependency/events_monitors_configure.h"
#include "../../src/global_business_dependency/service_interfaces/user/user_http_client.h"
#include "../common_test_funtions.h"
#include "../unit_test/bc/user/user_service_mock.h"
#include "../../src/bc/transfer/transfer_service_factory.h"
#include "../../src/bc/fund/fund_service_factory.h"
#include "../../src/bc/user/UserServiceFactory.h"

class RequireFlowTestForIntegrationEnvironment : public ::testing::Test {
 public:
  virtual void SetUp() {
    NamingServiceManager::GetInstance()->Add_Service<UserHttpService*>(
        "用户HTTP服务", UserHttpService::BuildInstance(RequireInterceptor::GetInstance()));
    NamingServiceManager::GetInstance()->Add_Service<FundHttpService*>(
        "FundHttpService", FundHttpService::BuildInstance(RequireInterceptor::GetInstance()));
    RequestionConfigure::GetInstance()->Add_Require_Mapping(
        "UserRequireMapping", UserRequireMapping::BuildInstance(UserServiceFactoryForIntegration::GetInstance()));
    RequestionConfigure::GetInstance()->Add_Require_Mapping(
        "TransferRequireMapping",
        TransferRequireMapping::BuildInstance(TransferServiceFactoryForIntegration::GetInstance()));

    RequestionConfigure::GetInstance()->Add_Require_Mapping(
        "FundRequireMapping", FundRequireMapping::BuildInstance(FundServiceFactoryForIntegration::GetInstance()));
    EventsMonitorsConfigure::RegisterEventMappings();
    init_fund_account(UserHttpClient::GetInstance());
  }
  virtual void TearDown() {
    UserHttpClient::DestroyInstance();
    UserHttpService::DestroyInstance();
    FundHttpClient::Destroy_Singleton();
    FundHttpService::Destroy_Singleton();

    FundServiceFactoryForIntegration::DestroyInstance();
    TransferServiceFactoryForIntegration::DestroyInstance();
    UserServiceFactory::DestroyInstance();

    EventsMonitorsConfigure::UnRegisterEventMappings();
    PublishSubscribeService::DestoryInstance();
    RequestionConfigure::DestroyInstance();

    UserRequireMapping::DestroyInstance();
    TransferRequireMapping::DestroyInstance();
    FundRequireMapping::DestroyInstance();
    NamingServiceManager::Destroy_Singleton();
  }
};
#endif  // TRANSFER_RequireFlowTestEnvironment_H
