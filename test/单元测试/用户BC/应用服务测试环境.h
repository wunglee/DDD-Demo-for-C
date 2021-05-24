#ifndef TRANSFER_应用服务测试环境_H
#define TRANSFER_应用服务测试环境_H
#include "用户查询模拟.h"
#include "用户仓储模拟.h"
#include "../../../src/全局配置/服务接口/用户服务接口.h"
#include "../../../src/用户BC/应用层/用户服务.h"
class 应用服务测试环境 : public ::testing::Test {
public:
    std::vector<用户> 用户集合_;
    用户仓储模拟 * 用户仓储模拟_= nullptr;
    用户查询模拟 * 用户查询模拟_= nullptr;
    virtual void SetUp() {
        用户仓储模拟_=用户仓储模拟::构建单例(用户集合_);
        用户查询模拟_=用户查询模拟::构建单例(用户集合_);
        用户服务::构建单例(用户仓储模拟_,用户查询模拟_);
    }
    virtual void TearDown() {
        delete 用户仓储模拟_;
        delete 用户查询模拟_;
        用户服务::销毁单例();
    }
};


#endif //TRANSFER_应用服务测试环境_H
