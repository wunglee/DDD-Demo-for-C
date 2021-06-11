#ifndef TRANSFER_RequireTestEnvironment1_H
#define TRANSFER_RequireTestEnvironment1_H
#include "gtest/gtest.h"
#include "../../../src/framework_components/requestion_filters/require_interceptor.h"
#include "../../../src/framework_components/naming_service/naming_service_manager.h"
#include "require_mapping_mock.h"
#include "require_filter_mock1.h"
#include "require_filter_mock2.h"
class RequireTestEnvironment1: public ::testing::Test {
public:
    RequireMapping * requireMapping= nullptr;
    virtual void SetUp() {
        requireMapping=new RequireMappingMock();
        RequireMappingsManager::BuildInstance()->Add_Require_Mapping("RequireMappingMock", requireMapping);
        NamingServiceManager::GetInstance()->Add_Service<RequireMappingsManager *>("RequireMappingsManager",
                                                                                     RequireMappingsManager::BuildInstance());
        NamingServiceManager::GetInstance()->Add_Service<RequireInterceptor *>("RequireInterceptor",
                                                                                 RequireInterceptor::GetInstance());
     }

    virtual void TearDown() {
        NamingServiceManager::Destroy_Singleton();
        RequireMappingsManager::Destroy_Singleton();
        RequireInterceptor::Destroy_Singleton();
        delete requireMapping;
    }
};


#endif //TRANSFER_RequireTestEnvironment1_H
