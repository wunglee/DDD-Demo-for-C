#ifndef TRANSFER_主适配器请求测试环境_H
#define TRANSFER_主适配器请求测试环境_H
#include "gtest/gtest.h"
#include "../../../src/用户BC/主适配器/用户请求处理器.h"
#include "../../../src/框架组件/本地请求拦截/请求处理配置器.h"
#include "用户服务模拟.h"
#include "../../../src/用户BC/主适配器/用户HTTP服务端.h"
class 主适配器请求测试环境 : public ::testing::Test {
public:
    virtual void SetUp() {
        请求处理配置器::获取单例()->注册请求处理器("用户请求处理器",用户请求处理器::构建单例(用户服务模拟::构造单例()));
        命名服务管理器::获取单例()->注册服务<用户HTTP服务端 *>("用户HTTP服务端", 用户HTTP服务端::构建单例(请求接收器::获取单例()));
    }
    virtual void TearDown() {
        请求处理配置器::销毁单例();
        用户请求处理器::销毁单例();
        用户服务模拟::销毁单例();
        用户HTTP服务端::销毁单例();
        命名服务管理器::销毁单例();
    }
};
#endif //TRANSFER_主适配器请求测试环境_H
