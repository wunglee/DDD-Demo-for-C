#ifndef TRANSFER_从适配器层测试环境_H
#define TRANSFER_从适配器层测试环境_H
#include "gtest/gtest.h"
#include "TransferDAOMock.h"
#include "../../../src/TransferBC/BackendAdapters/TransferRepository.h"

class 从适配器层转账仓储测试环境 : public ::testing::Test {
public:
    TransferDAOMock * 转账DAO模拟_= nullptr;
    UserServiceInterface * 用户服务接口_= nullptr;
    virtual void SetUp() {
        用户服务接口_= UserServiceMock::构造单例();
        转账DAO模拟_=TransferDAOMock::获取单例();
        TransferRepository::构建单例(转账DAO模拟_, 用户服务接口_);
    }
    virtual void TearDown() {
        delete 用户服务接口_;
        delete 转账DAO模拟_;
        TransferRepository::销毁单例();
    }
};


#endif //TRANSFER_从适配器层测试环境_H
