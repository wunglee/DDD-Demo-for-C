#include "user_repository_mock.h"
#include "user_query_mock.h"
#include "user_dao_mock.h"
#include "user_service_mock.h"

UserServiceMock* UserServiceMock::userServiceInterface_=nullptr;
UserRepositoryMock* UserRepositoryMock::userRepositoryMock=nullptr;
UserQueryMock* UserQueryMock::userQueryMock=nullptr;
UserDAOMock* UserDAOMock::userDAOMock=nullptr;
