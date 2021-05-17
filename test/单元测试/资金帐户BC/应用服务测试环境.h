#ifndef TRANSFER_应用服务测试环境_H
#define TRANSFER_应用服务测试环境_H
#include "资金帐户查询模拟.h"
#include "资金帐户仓储模拟.h"
class 应用服务测试环境 : public ::testing::Test {
public:
    std::vector<资金帐户> 资金帐户集合_;
    资金帐户仓储模拟 * 资金帐户仓储模拟_= nullptr;
    资金帐户查询模拟 * 资金帐户查询模拟_= nullptr;
    virtual void SetUp() {
        资金帐户仓储模拟_=资金帐户仓储模拟::构建单例(资金帐户集合_);
        资金帐户查询模拟_=资金帐户查询模拟::构建单例(资金帐户集合_);
        资金帐户服务::构建单例(资金帐户仓储模拟_,资金帐户查询模拟_);
    }
    virtual void TearDown() {
        delete 资金帐户仓储模拟_;
        delete 资金帐户查询模拟_;
        资金帐户服务::销毁单例();
    }
};
#endif //TRANSFER_应用服务测试环境_H
