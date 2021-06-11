#ifndef TRANSFER_UserFrontendEnvironment_H
#define TRANSFER_UserFrontendEnvironment_H
#include "gtest/gtest.h"
#include "../../../../src/bc/user/frontend_adapters/user_require_mapping.h"
#include "../../../../src/framework_components/requestion_filters/requestion_configure.h"
#include "user_service_mock.h"
#include "../../../../src/bc/user/frontend_adapters/user_http_service.h"
class UserFrontendEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::GetInstance()
        ->Add_Require_Mapping("UserRequireMapping",
                              UserRequireMapping::BuildInstance(UserServiceMock::BuildInstance()));
        NamingServiceManager::GetInstance()
        ->Add_Service<UserHttpService *>("UserHttpService",
                                         UserHttpService::BuildInstance(
                                                 RequireInterceptor::GetInstance()));
    }
    virtual void TearDown() {
        RequestionConfigure::DestroyInstance();
        UserRequireMapping::DestroyInstance();
        UserServiceMock::DestroyInstance();
        UserHttpService::DestroyInstance();
        NamingServiceManager::Destroy_Singleton();
    }
};
#endif //TRANSFER_UserFrontendEnvironment_H
