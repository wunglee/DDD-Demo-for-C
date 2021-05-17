#ifndef TRANSFER_从适配器仓储与查询测试环境_H
#define TRANSFER_从适配器仓储与查询测试环境_H
#include "gtest/gtest.h"
#include "资金帐户DAO模拟.h"
#include "../../../src/资金帐户BC/从适配器/资金帐户仓储.h"
#include "../../../src/资金帐户BC/从适配器/资金帐户DAO接口.h"
#include "../../../src/资金帐户BC/应用层/资金帐户仓储接口.h"
#include "../../../src/资金帐户BC/应用层/资金帐户查询接口.h"
#include "../../../src/资金帐户BC/应用层/资金帐户服务.h"
#include "../../../src/资金帐户BC/从适配器/资金帐户查询.h"
class 从适配器仓储与查询测试环境 : public ::testing::Test {
public:
    资金帐户DAO接口 * 资金帐户DAO接口_= nullptr;
    virtual void SetUp() {
        资金帐户DAO接口_= 资金帐户DAO模拟::构建单例();
        资金帐户仓储::构建单例(资金帐户DAO接口_);
        资金帐户查询::构建单例(资金帐户DAO接口_);
    }
    virtual void TearDown() {
       delete 资金帐户DAO接口_;
        资金帐户仓储::销毁单例();
        资金帐户查询::销毁单例();
    }
};


#endif //TRANSFER_从适配器仓储与查询测试环境_H
