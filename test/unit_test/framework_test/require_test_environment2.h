#ifndef TRANSFER_RequireTestEnvironment2_H
#define TRANSFER_RequireTestEnvironment2_H
#include "gtest/gtest.h"
#include "../../../src/framework_components/requestion_filters/require_interceptor.h"
#include "../../../src/framework_components/naming_service/naming_service_manager.h"
#include "require_mapping_mock.h"
#include "require_filter_mock1.h"
#include "require_filter_mock2.h"
class RequireTestEnvironment2: public ::testing::Test {
public:
    RequireMapping * requireMapping= nullptr;
    RequireFilterMock1 * requireFilterMock1= nullptr;
    RequireFilterMock2 * requireFilterMock2= nullptr;
    std::list<Filter*> filters;
    virtual void SetUp() {
        requireMapping=new RequireMappingMock();
        requireFilterMock1=new RequireFilterMock1("拦截1");
        requireFilterMock2=new RequireFilterMock2("拦截2");
        filters.assign({requireFilterMock1, requireFilterMock2});
        RequireMappingsManager* requireMappingsManager= RequireMappingsManager::BuildInstance(filters);
        requireMappingsManager->Add_Require_Mapping("RequireMappingMock", requireMapping);
        NamingServiceManager::GetInstance()->Add_Service<RequireMappingsManager *>("RequireMappingsManager",
                                                                                   requireMappingsManager);
     }

    virtual void TearDown() {
        RequireMappingsManager::Destroy_Singleton();
        delete requireMapping;
        RequireInterceptor::Destroy_Singleton();
        filters.clear();
        delete requireFilterMock1;
        delete requireFilterMock2;
        NamingServiceManager::Destroy_Singleton();
    }
};


#endif //TRANSFER_RequireTestEnvironment2_H
