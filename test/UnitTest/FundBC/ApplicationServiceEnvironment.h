#ifndef TRANSFER_应用服务测试环境_H
#define TRANSFER_应用服务测试环境_H
#include "FundQueryMock.h"
#include "FundRepositoryMock.h"
class ApplicationServiceEnvironment : public ::testing::Test {
public:
    std::vector<Fund> 资金帐户集合_;
    FundRepositoryMock * 资金帐户仓储模拟_= nullptr;
    FundQueryMock * 资金帐户查询模拟_= nullptr;
    virtual void SetUp() {
        资金帐户仓储模拟_=FundRepositoryMock::构建单例(资金帐户集合_);
        资金帐户查询模拟_=FundQueryMock::构建单例(资金帐户集合_);
        FundService::构建单例(资金帐户仓储模拟_, 资金帐户查询模拟_);
    }
    virtual void TearDown() {
        delete 资金帐户仓储模拟_;
        delete 资金帐户查询模拟_;
        FundService::销毁单例();
    }
};
#endif //TRANSFER_应用服务测试环境_H
