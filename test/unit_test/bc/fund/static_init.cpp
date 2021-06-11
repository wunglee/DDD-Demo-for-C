#include "fund_service_mock.h"
#include "fund_dao_mock.h"
#include "fund_repository_mock.h"
#include "fund_query_mock.h"

FundServiceMock * FundServiceMock::fundServiceMock= nullptr;
FundDAOMock* FundDAOMock::fundDAOMock=nullptr;
FundRepositoryMock* FundRepositoryMock::fundRepositoryMock=nullptr;
FundQueryMock* FundQueryMock::fundQueryMock=nullptr;