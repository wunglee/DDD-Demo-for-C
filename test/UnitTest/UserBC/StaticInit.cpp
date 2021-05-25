#include "UserRepositoryMock.h"
#include "UserQueryMock.h"
#include "UserDAOMock.h"
#include "UserServiceMock.h"

UserServiceMock* UserServiceMock::用户服务模拟_=nullptr;
UserRepositoryMock* UserRepositoryMock::用户仓储模拟_=nullptr;
UserQueryMock* UserQueryMock::用户查询模拟_=nullptr;
UserDAOMock* UserDAOMock::用户DAO模拟_=nullptr;
