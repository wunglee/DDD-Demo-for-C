#ifndef TRANSFER_从适配器仓储与查询测试环境_H
#define TRANSFER_从适配器仓储与查询测试环境_H
#include "../../../src/用户BC/从适配器/用户仓储.h"
#include "../../../src/用户BC/从适配器/用户查询.h"
#include "../../../src/用户BC/从适配器/用户DAO接口.h"
#include "../../../src/用户BC/应用层/用户仓储接口.h"
#include "../../../src/用户BC/应用层/用户查询接口.h"
#include "用户DAO模拟.h"

class 从适配器仓储与查询测试环境: public ::testing::Test {
public:
    用户DAO接口 * 用户DAO接口_= nullptr;
    virtual void SetUp() {
        用户DAO接口_=用户DAO模拟::构建单例();
        用户仓储::构建单例(用户DAO接口_);
        用户查询::构建单例(用户DAO接口_);
    }
    virtual void TearDown() {
        delete 用户DAO接口_;
    }
};


#endif //TRANSFER_从适配器仓储与查询测试环境_H
