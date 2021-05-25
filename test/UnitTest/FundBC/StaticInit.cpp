#include "FundServiceMock.h"
#include "FundDAOMock.h"
#include "FundRepositoryMock.h"
#include "FundQueryMock.h"

FundServiceMock * FundServiceMock::资金帐户请求服务_= nullptr;
FundDAOMock* FundDAOMock::资金帐户DAO模拟_=nullptr;
FundRepositoryMock* FundRepositoryMock::资金帐户仓储模拟_=nullptr;
FundQueryMock* FundQueryMock::资金帐户查询模拟_=nullptr;