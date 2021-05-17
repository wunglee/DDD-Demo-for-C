#include "gtest/gtest.h"
#include "从适配器仓储与查询测试环境.h"
#include "应用服务测试环境.h"
#include "../../../src/用户BC/从适配器/用户DAO.h"
TEST_F(应用服务测试环境, 添加用户){
    用户服务::获取单例()->添加用户("XX");
    ASSERT_EQ(用户服务::获取单例()->获取用户("XX").has_value(), true);
}
void 测试冻结用户(){
    用户服务::获取单例()->添加用户("XX");
    用户服务::获取单例()->冻结用户("XX");
    ASSERT_EQ(用户服务::获取单例()->获取用户("XX")->是否冻结(), true);
    }
TEST_F(应用服务测试环境, 解冻用户){
    测试冻结用户();
}
TEST_F(应用服务测试环境, 冻结用户){
    测试冻结用户();
    用户服务::获取单例()->解冻用户("XX");
    ASSERT_EQ(用户服务::获取单例()->获取用户("XX")->是否冻结(), false);
}
TEST_F(从适配器仓储与查询测试环境, 添加用户){
    用户仓储::获取单例()->添加用户("XX");
    ASSERT_EQ(用户查询::获取单例()->获取用户("XX").has_value(), true);
}
TEST(DAO测试,获取用户PO){
    用户DAO::构建单例()->添加用户PO(用户PO("XX"));
    ASSERT_EQ(用户DAO::构建单例()->获取用户PO("XX").has_value(), true);
}
TEST(DAO测试,更新用户PO){
    用户DAO::构建单例()->添加用户PO(用户PO("XX"));
    用户DAO::构建单例()->更新用户PO(用户PO("XX",true));
    ASSERT_EQ(用户DAO::构建单例()->获取用户PO("XX")->是否冻结_, true);
}