#include "gtest/gtest.h"
#include "UserBackendEnvironment.h"
#include "ApplicatiionServiceEnvironment.h"
#include "../../../src/UserBC/BackendAdapters/UserDAO.h"
#include "UserFrontendEnvironment.h"

TEST_F(ApplicationServiceEnvironment, 添加用户){
    UserService::获取单例()->添加用户("XX");
    ASSERT_EQ(UserService::获取单例()->获取用户("XX").has_value(), true);
}
void 测试冻结用户(){
    UserService::获取单例()->添加用户("XX");
    UserService::获取单例()->冻结用户("XX");
    ASSERT_EQ(UserService::获取单例()->获取用户("XX")->是否冻结(), true);
    }
TEST_F(ApplicationServiceEnvironment, 解冻用户){
    测试冻结用户();
}
TEST_F(ApplicationServiceEnvironment, 冻结用户){
    测试冻结用户();
    UserService::获取单例()->解冻用户("XX");
    ASSERT_EQ(UserService::获取单例()->获取用户("XX")->是否冻结(), false);
}
TEST_F(FundBackendEnvironment, 添加用户){
    UserRepository::获取单例()->添加用户("XX");
    ASSERT_EQ(UserQuery::获取单例()->获取用户("XX").has_value(), true);
}
TEST(DAO测试,获取用户PO){
    UserDAO::构建单例()->添加用户PO(UserPO("XX"));
    ASSERT_EQ(UserDAO::构建单例()->获取用户PO("XX").has_value(), true);
}
TEST(DAO测试,更新用户PO){
    UserDAO::构建单例()->添加用户PO(UserPO("XX"));
    UserDAO::构建单例()->更新用户PO(UserPO("XX", true));
    ASSERT_EQ(UserDAO::构建单例()->获取用户PO("XX")->是否冻结_, true);
}

TEST_F(TransferFrontendEnvironment, 通过主适配器添加用户){
    UserHttpService::获取单例()->添加用户("XX");
    ASSERT_EQ(UserServiceMock::获取单例()->获取用户("XX").has_value(), true);
}
TEST_F(TransferFrontendEnvironment, 通过主适配器获取用户){
    UserHttpService::获取单例()->添加用户("XX");
    ASSERT_EQ(UserHttpService::获取单例()->获取用户("XX").has_value(), true);
}
TEST_F(TransferFrontendEnvironment, 通过主适配器冻结用户){
    UserHttpService::获取单例()->添加用户("XX");
    UserHttpService::获取单例()->冻结用户("XX");
    ASSERT_EQ(UserServiceMock::获取单例()->获取用户("XX")->是否冻结(), true);
}
TEST_F(TransferFrontendEnvironment, 通过主适配器解冻用户){
    UserHttpService::获取单例()->添加用户("XX");
    UserHttpService::获取单例()->冻结用户("XX");
    UserHttpService::获取单例()->解冻用户("XX");
    ASSERT_EQ(UserServiceMock::获取单例()->获取用户("XX")->是否冻结(), false);
}
TEST_F(TransferFrontendEnvironment, 通过主适配器获取冻结状态){
    UserHttpService::获取单例()->添加用户("XX");
    UserHttpService::获取单例()->冻结用户("XX");
    ASSERT_EQ(UserHttpService::获取单例()->是否已冻结("XX"), true);
}