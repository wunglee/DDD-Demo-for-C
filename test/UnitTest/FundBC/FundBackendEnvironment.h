#ifndef TRANSFER_从适配器仓储与查询测试环境_H
#define TRANSFER_从适配器仓储与查询测试环境_H
#include "gtest/gtest.h"
#include "FundDAOMock.h"
#include "../../../src/FundBC/BackendAdapters/FundRepository.h"
#include "../../../src/FundBC/BackendAdapters/FundDAOInterface.h"
#include "../../../src/FundBC/Application/FundRepositoryInterface.h"
#include "../../../src/FundBC/Application/FundServiceQueryInterface.h"
#include "../../../src/FundBC/Application/FundService.h"
#include "../../../src/FundBC/BackendAdapters/FundQuery.h"
class FundBackendEnvironment : public ::testing::Test {
public:
    FundDAOInterface * 资金帐户DAO接口_= nullptr;
    virtual void SetUp() {
        资金帐户DAO接口_= FundDAOMock::构建单例();
        FundRepository::构建单例(资金帐户DAO接口_);
        FundQuery::构建单例(资金帐户DAO接口_);
    }
    virtual void TearDown() {
       delete 资金帐户DAO接口_;
        FundRepository::销毁单例();
        FundQuery::销毁单例();
    }
};


#endif //TRANSFER_从适配器仓储与查询测试环境_H
