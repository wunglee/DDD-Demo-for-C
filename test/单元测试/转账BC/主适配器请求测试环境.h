#ifndef TRANSFER_主适配器请求测试环境_H
#define TRANSFER_主适配器请求测试环境_H
#include "gtest/gtest.h"
#include "../../../src/转账BC/主适配器/转账请求处理器.h"
#include "../../../src/框架组件/请求拦截/请求处理管理器.h"
#include "../../../src/转账BC/应用层/转账服务接口.h"

#include "转账服务模拟.h"
#include "../../../src/转账BC/主适配器/Protobuf请求适配器.h"
class 主适配器请求测试环境 : public ::testing::Test {
public:
    virtual void SetUp() {
        请求处理管理器::获取单例();
        请求处理器管理器::获取单例()->注册请求处理器("转账请求处理器",转账请求处理器::构建单例(转账服务模拟::获取单例()));
        命名服务管理器::获取单例()->注册服务<Protobuf请求适配器 *>("Protobuf请求适配器", Protobuf请求适配器::构建单例(请求接收器::获取单例()));
    }
    virtual void TearDown() {
        请求处理管理器::销毁单例();
        转账请求处理器::销毁单例();
        转账服务模拟::销毁单例();
        Protobuf请求适配器::销毁单例();
        命名服务管理器::销毁单例();

    }
};
#endif //TRANSFER_主适配器请求测试环境_H
