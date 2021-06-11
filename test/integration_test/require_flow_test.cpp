#include "gtest/gtest.h"

#include "require_flow_test_for_integration_environment.h"
#include "../../src/bc/fund/fund_service_factory.h"

TEST_F(RequireFlowTestForIntegrationEnvironment, create_fund_after_create_user) {
  boost::optional<FundDTO> fund1 = FundServiceFactory::GetInstance(
          FundMenoryDAO::GetInstance())->GetFund("XX");
  boost::optional<FundDTO> fund2 = FundServiceFactory::GetInstance(
          FundMenoryDAO::GetInstance())->GetFund("YY");
  ASSERT_EQ(fund1.has_value(), true);
  ASSERT_EQ(fund2.has_value(), true);
  ASSERT_EQ(fund1.value().account_id_, "XX");
  ASSERT_EQ(fund2.value().account_id_, "YY");
}
void setForbid(bool forbid_out, bool forbid_in) {
  if (forbid_out) {
      FundServiceFactory::GetInstance(FundMenoryDAO::GetInstance())->SetForbidIn("XX", true);
  }
  if (forbid_in) {
      FundServiceFactory::GetInstance(FundMenoryDAO::GetInstance())->SetForbidOut("YY", true);
  }
}
int create_transfer(float amount_in_fund, float amount) {
    FundServiceFactory::GetInstance(FundMenoryDAO::GetInstance())->Initialize("XX", amount_in_fund);
  return TransferService::GetInstance()->ApplyTransfer("XX", "YY", amount);
}
TEST_F(RequireFlowTestForIntegrationEnvironment, transfer_create_success) {
  check_transfer(create_transfer(1000, 100), Transfer::Created);
}

TEST_F(RequireFlowTestForIntegrationEnvironment, create_transfer_when_payer_forbid_out) {
  PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("扣减已失败", "TransferEventMonitor");
  setForbid(true, false);
  check_transfer(create_transfer(1000, 100), Transfer::Canceled);
}
TEST_F(RequireFlowTestForIntegrationEnvironment, create_transfer_when_payer_amount_not_enough) {
  PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("扣减已失败", "TransferEventMonitor");
  check_transfer(create_transfer(100, 1000), Transfer::Canceled);
}
TEST_F(RequireFlowTestForIntegrationEnvironment, create_transfer_and_sub_amount_the_payer_fund) {
  PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("扣减已成功", "TransferEventMonitor");
  check_transfer(create_transfer(1000, 100), Transfer::Payer_Deducted);
}
TEST_F(RequireFlowTestForIntegrationEnvironment, create_transfer_when_payee_forbid_in) {
  PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("扣减已成功", "TransferEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("转账已出账", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("增资已失败", "TransferEventMonitor");
  setForbid(false, true);
  check_transfer(create_transfer(1000, 100), Transfer::Applying_Refund);
}

TEST_F(RequireFlowTestForIntegrationEnvironment, finish_tranfer) {
  PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("扣减已成功", "TransferEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("转账已出账", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("增资已成功", "TransferEventMonitor");
  check_transfer(create_transfer(1000, 100), Transfer::Payee_Increased);
}
TEST_F(RequireFlowTestForIntegrationEnvironment, finish_refund) {
  PublishSubscribeService::GetInstance()->Subscribe("转账已创建", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("扣减已成功", "TransferEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("转账已出账", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("增资已失败", "TransferEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("转账退款中", "FundEventMonitor");
  PublishSubscribeService::GetInstance()->Subscribe("增资已成功", "TransferEventMonitor");
  setForbid(false, true);
  check_transfer(create_transfer(1000, 100), Transfer::Refunded);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}