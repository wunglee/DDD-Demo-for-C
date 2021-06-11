#ifndef TRANSFER_UserBackendEnvironment_H
#define TRANSFER_UserBackendEnvironment_H
#include "../../../../src/bc/user/backend_adapters/user_repository.h"
#include "../../../../src/bc/user/backend_adapters/user_query.h"
#include "../../../../src/bc/user/backend_adapters/user_dao_interface.h"
#include "../../../../src/bc/user/application/user_repository_interface.h"
#include "../../../../src/bc/user/application/user_query_service.h"
#include "user_dao_mock.h"

class UserBackendEnvironment: public ::testing::Test {
public:
    UserDAOInterface * userDAOInterface_= nullptr;
    virtual void SetUp() {
        userDAOInterface_=UserDAOMock::BuildInstance();
        UserRepository::BuildInstance(userDAOInterface_);
        UserQuery::BuildInstance(userDAOInterface_);
    }
    virtual void TearDown() {
        delete userDAOInterface_;
    }
};


#endif //TRANSFER_UserBackendEnvironment_H
