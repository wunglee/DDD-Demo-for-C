#ifndef TRANSFER_UserBackendEnvironment_H
#define TRANSFER_UserBackendEnvironment_H
#include "gtest/gtest.h"
#include "fund_dao_mock.h"
#include "../../../../src/bc/fund/backend_adapters/fund_repository.h"
#include "../../../../src/bc/fund/backend_adapters/fund_dao_interface.h"
#include "../../../../src/bc/fund/application/fund_repository_interface.h"
#include "../../../../src/bc/fund/application/fund_service_query_interface.h"
#include "../../../../src/bc/fund/application/fund_service.h"
#include "../../../../src/bc/fund/backend_adapters/fund_query.h"
class UserBackendEnvironment : public ::testing::Test {
public:
    FundDAOInterface * fundDAOInterface_= nullptr;
    virtual void SetUp() {
        fundDAOInterface_= FundDAOMock::BuildInstance();
        FundRepository::BuildInstance(fundDAOInterface_);
        FundQuery::BuildInstance(fundDAOInterface_);
    }
    virtual void TearDown() {
       delete fundDAOInterface_;
        FundRepository::DestroyInstance();
        FundQuery::DestroyInstance();
    }
};


#endif //TRANSFER_UserBackendEnvironment_H
