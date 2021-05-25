#ifndef TRANSFER_从适配器仓储与查询测试环境_H
#define TRANSFER_从适配器仓储与查询测试环境_H
#include "../../../src/UserBC/BackendAdapters/UserRepository.h"
#include "../../../src/UserBC/BackendAdapters/UserQuery.h"
#include "../../../src/UserBC/BackendAdapters/UserDAOInterface.h"
#include "../../../src/UserBC/Application/UserRepositoryInterface.h"
#include "../../../src/UserBC/Application/UserQueryService.h"
#include "UserDAOMock.h"

class FundBackendEnvironment: public ::testing::Test {
public:
    UserDAOInterface * 用户DAO接口_= nullptr;
    virtual void SetUp() {
        用户DAO接口_=UserDAOMock::构建单例();
        UserRepository::构建单例(用户DAO接口_);
        UserQuery::构建单例(用户DAO接口_);
    }
    virtual void TearDown() {
        delete 用户DAO接口_;
    }
};


#endif //TRANSFER_从适配器仓储与查询测试环境_H
