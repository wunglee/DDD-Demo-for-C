#ifndef TRANSFER_应用层测试环境_H
#define TRANSFER_应用层测试环境_H
#include "../用户BC/用户服务模拟.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "../../../src/转账BC/应用层/转账服务.h"
#include "转账仓储模拟.h"
#include "转账查询模拟.h"
class 应用层测试环境 : public ::testing::Test {
public:
    std::vector<转账> 转账集合_;
    转账仓储模拟 * 转账仓储模拟_= nullptr;
    转账查询模拟 * 转账查询模拟_= nullptr;
    用户服务接口 * 用户服务模拟_= nullptr;
    virtual void SetUp() {
        用户服务模拟_= 用户服务模拟::构造单例();
        命名服务管理器::获取单例()->注册服务("用户服务", (用户服务接口 *) 用户服务模拟_);
        转账仓储模拟_=转账仓储模拟::获取单例(转账集合_, 用户服务模拟_);
        转账查询模拟_=转账查询模拟::获取单例(转账集合_);
        命名服务管理器::获取单例()->注册服务("转账服务", (转账服务接口 *) 转账服务::构建单例(转账仓储模拟_, 转账查询模拟_,用户服务模拟_));
    }
    virtual void TearDown() {
        delete 命名服务管理器::获取单例()->注销服务<用户服务接口 *>("用户服务").value();
        命名服务管理器::获取单例()->注销服务<转账服务接口 *>("转账服务").value();
        转账服务::销毁单例();
        delete 转账仓储模拟_;
        delete 转账查询模拟_;
        转账集合_.clear();
        命名服务管理器::销毁单例();
    }
};


#endif //TRANSFER_应用层测试环境_H
