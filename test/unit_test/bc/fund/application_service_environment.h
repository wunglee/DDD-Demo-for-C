#ifndef TRANSFER_ApplicationServiceEnvironment_H
#define TRANSFER_ApplicationServiceEnvironment_H
#include "../../../../src/bc/fund/application/fund_service.h"
#include "fund_query_mock.h"
#include "fund_repository_mock.h"

class ApplicationServiceEnvironment : public ::testing::Test {
 public:
  std::vector<Fund> funds;
  FundRepositoryMock* fundRepositoryMock = nullptr;
  FundQueryMock* fundQueryMock = nullptr;
  virtual void SetUp() {
    fundRepositoryMock = FundRepositoryMock::BuildInstance(funds);
    fundQueryMock = FundQueryMock::BuildInstance(funds);
    FundService::BuildInstance(fundRepositoryMock, fundQueryMock);
  }
  virtual void TearDown() {
    delete fundRepositoryMock;
    delete fundQueryMock;
    FundService::DestoryInstance();
  }
};
#endif  // TRANSFER_ApplicationServiceEnvironment_H
