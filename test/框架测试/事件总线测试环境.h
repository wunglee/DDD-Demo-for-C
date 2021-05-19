#ifndef TRANSFER_事件总线测试环境_H
#define TRANSFER_事件总线测试环境_H
#include "gtest/gtest.h"
#include "事件监听器模拟.h"
#include "../../src/框架组件/事件总线/事件发布订阅服务.h"
#include "../../src/框架组件/命名服务/命名服务管理器.h"

class 事件总线测试环境 : public ::testing::Test {
public:
    virtual void SetUp() {
        命名服务管理器::获取单例()->注册服务("事件监听器模拟", (事件监听器 *) new 事件监听器模拟());
        事件发布订阅服务::构建单例()->订阅("转账已创建", "事件监听器模拟");
    }
    virtual void TearDown() {
        delete 命名服务管理器::获取单例()->注销服务<事件监听器 *>("事件监听器模拟").value();
        事件发布订阅服务::销毁单例();
        命名服务管理器::销毁单例();
    }
};


#endif //TRANSFER_事件总线测试环境_H
