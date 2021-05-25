#ifndef TRANSFER_主适配器事件测试环境_H
#define TRANSFER_主适配器事件测试环境_H
#include "gtest/gtest.h"
#include "../../../src/资金帐户BC/主适配器/资金事件处理器.h"
#include "../../../src/资金帐户BC/应用层/资金帐户服务接口.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "../../../src/框架组件/事件发布订阅/事件发布订阅服务.h"
#include "../../../src/框架组件/事件发布订阅/事件监听器.h"
#include "资金帐户服务模拟.h"

class 主适配器事件测试环境 : public ::testing::Test {
public:
    资金帐户服务模拟* 资金帐户服务模拟_=资金帐户服务模拟::获取单例();
    virtual void SetUp() {
        命名服务管理器::获取单例()->注册服务("资金帐户服务", (资金帐户服务接口 *) 资金帐户服务模拟_);
        命名服务管理器::获取单例()->注册服务("资金事件处理器", (事件监听器 *) 资金事件处理器::构建单例(资金帐户服务模拟::获取单例()));
        事件发布订阅服务::构建单例()->订阅("转账已创建", "资金事件处理器");
        事件发布订阅服务::构建单例()->订阅("用户已创建", "资金事件处理器");
        事件发布订阅服务::构建单例()->订阅("转账已出账", "资金事件处理器");
        事件发布订阅服务::构建单例()->订阅("转账退款中", "资金事件处理器");
    }
    virtual void TearDown() {
        delete 命名服务管理器::获取单例()->注销服务<事件监听器 *>("资金事件处理器").value();
        delete 命名服务管理器::获取单例()->注销服务<资金帐户服务接口 *>("资金帐户服务").value();
        delete 资金帐户服务模拟::获取单例();
        事件发布订阅服务::销毁单例();
    }
};
#endif //TRANSFER_主适配器事件测试环境_H
