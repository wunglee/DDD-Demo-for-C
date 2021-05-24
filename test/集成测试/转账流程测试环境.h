#ifndef TRANSFER_转账流程测试环境_H
#define TRANSFER_转账流程测试环境_H
#include "../../src/框架组件/命名服务/命名服务管理器.h"
#include "gtest/gtest.h"
#include "../../src/资金帐户BC/资金帐户服务工厂.h"
#include "../../src/用户BC/用户服务工厂.h"
#include "../../src/用户BC/主适配器/用户HTTP服务端.h"
#include "../../src/转账BC/转帐服务工厂.h"
#include "../单元测试/转账BC/用户服务模拟.h"
#include "../../src/全局配置/事件监听器配置.h"
#include "../../src/转账BC/从适配器/用户HTTP客户端.h"
class 转账流程测试环境 : public ::testing::Test {
public:
    virtual void SetUp() {
        命名服务管理器::获取单例()->注册服务("用户HTTP服务",用户HTTP服务端::构建单例(用户服务工厂::获取单例()));
        事件监听器配置::注册事件处理器();
    }
    virtual void TearDown() {
        命名服务管理器::获取单例()->注销服务<用户HTTP服务端 *>("用户HTTP服务").value();

        事件监听器配置::注销事件处理器();
        用户HTTP服务端::销毁单例();
        资金帐户服务工厂::销毁单例();
        转帐服务工厂::销毁单例();

        命名服务管理器::销毁单例();
        事件发布订阅服务::销毁单例();
    }




};
#endif //TRANSFER_转账流程测试环境_H
