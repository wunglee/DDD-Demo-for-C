#ifndef TRANSFER_应用服务测试环境_H
#define TRANSFER_应用服务测试环境_H
#include "UserQueryMock.h"
#include "UserRepositoryMock.h"
#include "../../../src/GlobalBusinessDependency/ServiceInterfaces/UserServiceInterface.h"
#include "../../../src/UserBC/Application/UserService.h"
class ApplicationServiceEnvironment : public ::testing::Test {
public:
    std::vector<User> 用户集合_;
    UserRepositoryMock * 用户仓储模拟_= nullptr;
    UserQueryMock * 用户查询模拟_= nullptr;
    virtual void SetUp() {
        用户仓储模拟_=UserRepositoryMock::构建单例(用户集合_);
        用户查询模拟_=UserQueryMock::构建单例(用户集合_);
        UserService::构建单例(用户仓储模拟_, 用户查询模拟_);
    }
    virtual void TearDown() {
        delete 用户仓储模拟_;
        delete 用户查询模拟_;
        UserService::销毁单例();
    }
};


#endif //TRANSFER_应用服务测试环境_H
