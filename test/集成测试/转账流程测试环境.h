#ifndef TRANSFER_转账流程测试环境_H
#define TRANSFER_转账流程测试环境_H
#include "../../src/框架组件/命名服务/命名服务管理器.h"
#include "gtest/gtest.h"
#include "../../src/资金帐户BC/资金帐户服务工厂.h"
#include "../../src/用户BC/用户服务工厂.h"
#include "../../src/用户BC/主适配器/用户HTTP服务端.h"
#include "../../src/用户BC/主适配器/用户请求处理器.h"
#include "../../src/转账BC/转帐服务工厂.h"
#include "../单元测试/用户BC/用户服务模拟.h"
#include "../../src/全局业务依赖/事件监听器配置.h"
#include "../../src/框架组件/请求拦截/请求处理配置器.h"
#include "../../src/转账BC/从适配器/用户HTTP客户端.h"
#include "../公共测试方法.h"


class 转账流程测试环境 : public ::testing::Test {
public:
    virtual void SetUp() {
        请求处理配置器::获取单例()->注册请求处理器("用户请求处理器",用户请求处理器::构建单例(用户服务工厂::获取单例()));
        命名服务管理器::获取单例()->注册服务<用户HTTP服务端 *>("用户HTTP服务", 用户HTTP服务端::构建单例(请求接收器::获取单例()));
        事件监听器配置::注册事件处理器();
        初始化资金帐户(用户HTTP客户端::获取单例());
    }
    virtual void TearDown() {
        用户HTTP客户端::销毁单例();
        用户HTTP服务端::销毁单例();

        资金帐户服务工厂::销毁单例();
        转帐服务工厂::销毁单例();
        用户服务工厂::销毁单例();

        事件监听器配置::注销事件处理器();
        事件发布订阅服务::销毁单例();
        请求处理配置器::销毁单例();

        用户请求处理器::销毁单例();
        命名服务管理器::销毁单例();
    }




};
#endif //TRANSFER_转账流程测试环境_H
