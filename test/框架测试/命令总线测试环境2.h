#ifndef TRANSFER_命令总线测试环境2_H
#define TRANSFER_命令总线测试环境2_H
#include "gtest/gtest.h"
#include "../../src/框架组件/命令总线/命令接收器.h"
#include "../../src/框架组件/命令总线/命令队列池接口.h"
#include "../../src/框架组件/命令总线/命令队列池.h"
#include "../../src/框架组件/命名服务/命名服务管理器.h"
#include "模拟处理器.h"
#include "命令拦截器模拟1.h"
#include "命令拦截器模拟2.h"
class 命令总线测试环境2: public ::testing::Test {
public:
    命令处理器 * 模拟处理器_= nullptr;
    命令拦截器模拟1 * 命令拦截器模拟1_= nullptr;
    命令拦截器模拟2 * 命令拦截器模拟2_= nullptr;
    std::list<命令拦截器*> 命令拦截器列表;
    virtual void SetUp() {
        命名服务管理器::获取单例()->注册服务<命令队列池接口 *>("命令队列池", new 命令队列池(10));
        模拟处理器_=new 模拟处理器();
        命令拦截器模拟1_=new 命令拦截器模拟1("拦截1");
        命令拦截器模拟2_=new 命令拦截器模拟2("拦截2");
        命令拦截器列表.assign({命令拦截器模拟1_,命令拦截器模拟2_});
        命令处理器管理器* 命令处理器管理器_=new 命令处理器管理器(命令拦截器列表);
        命令处理器管理器_->注册命令处理器("模拟处理器", 模拟处理器_);
        命名服务管理器::获取单例()->注册服务<命令处理器管理器 *>("命令处理器管理器", 命令处理器管理器_);
     }

    virtual void TearDown() {
        delete 命名服务管理器::获取单例()->注销服务<命令队列池接口 *>("命令队列池").value();
        delete 命名服务管理器::获取单例()->注销服务<命令处理器管理器 *>("命令处理器管理器").value();
        delete 模拟处理器_;
        命令接收器::销毁单例();
        命令拦截器列表.clear();
        delete 命令拦截器模拟1_;
        delete 命令拦截器模拟2_;
        命名服务管理器::销毁单例();
    }
};


#endif //TRANSFER_命令总线测试环境2_H
