#ifndef TRANSFER_从适配器层测试环境_H
#define TRANSFER_从适配器层测试环境_H
#include "gtest/gtest.h"
#include "转账DAO模拟.h"
#include "../../../src/转账BC/从适配器/转账仓储.h"

class 从适配器层转账仓储测试环境 : public ::testing::Test {
public:
    转账DAO模拟 * 转账DAO模拟_= nullptr;
    用户服务接口 * 用户服务接口_= nullptr;
    virtual void SetUp() {
        用户服务接口_= 用户服务模拟::构造单例();
        转账DAO模拟_=转账DAO模拟::获取单例();
        转账仓储::构建单例(转账DAO模拟_,用户服务接口_);
    }
    virtual void TearDown() {
        delete 用户服务接口_;
        delete 转账DAO模拟_;
        转账仓储::销毁单例();
    }
};


#endif //TRANSFER_从适配器层测试环境_H
