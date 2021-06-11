#include "gtest/gtest.h"

#include "../../../../src/bc/fund/backend_adapters/fund_menory_dao.h"
#include "../../../../src/bc/fund/frontend_adapters/fund_http_service.h"
#include "../../../../src/global_business_dependency/service_interfaces/fund/fund_http_client.h"
#include "application_service_environment.h"
#include "fund_backend_environment.h"
#include "fund_frontend_environment_for_command.h"
#include "fund_frontend_environment_for_event.h"

TEST_F(FundFrontendEnvironmentForEvent, on_transfer_created_event) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("转账已创建", 0, Refund_Created_DTO(0, "XX", 1).Serialize()));
  ASSERT_EQ(fundServiceMock->amount_subed, true);
}
TEST_F(FundFrontendEnvironmentForEvent, on_account_added_event) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("用户已创建", 0, UserCreatedDTO("XX").Serialize()));
  ASSERT_EQ(fundServiceMock->account_added, true);
}
TEST_F(FundFrontendEnvironmentForEvent, on_payer_deducted_event) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("转账已出账", 0, Payer_Deducted_DTO(0, "YY", 1).Serialize()));
  ASSERT_EQ(fundServiceMock->amount_added, true);
}
TEST_F(FundFrontendEnvironmentForEvent, on_apply_refund_event) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("转账退款中", 0, Refund_DTO(0, "XX", 1).Serialize()));
  ASSERT_EQ(fundServiceMock->amount_refunded, true);
}
Fund create_fund_account(std::string account_id) {
  Fund fund(account_id);
  FundRepository::GetInstance()->Create(fund);
  return fund;
}
TEST_F(UserBackendEnvironment, add_fund_account) {
  create_fund_account("XX");
  ASSERT_EQ(FundQuery::GetInstance()->GetFund("XX")->GetAccount(), "XX");
}
TEST_F(UserBackendEnvironment, update_fund_account) {
  std::string account_id = "XX";
  create_fund_account(account_id);
  Fund fundPO_ = Fund(account_id, false, false, 5, 0);
  FundRepository::GetInstance()->Update(fundPO_);
  ASSERT_EQ(FundQuery::GetInstance()->GetFund(account_id)->Get_Amount(), 5);
}
TEST_F(ApplicationServiceEnvironment, add_fund_account) {
  FundService::GetInstance()->AddFundAccount("XX");
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX").has_value(), true);
}
TEST_F(ApplicationServiceEnvironment, init_fund) {
  FundService::GetInstance()->AddFundAccount("XX");
  FundService::GetInstance()->Initialize("XX", 10);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 10);
}
void init_fund(std::string account_id, float amount) {
  FundService::GetInstance()->AddFundAccount(account_id);
  FundService::GetInstance()->Initialize(account_id, amount);
}
TEST_F(ApplicationServiceEnvironment, increase_amount) {
  init_fund("XX", 10);
  FundService::GetInstance()->Increase(1, "XX", 10);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 20);
}
TEST_F(ApplicationServiceEnvironment, decrease_amount) {
  init_fund("XX", 10);
  FundService::GetInstance()->Decrease(1, "XX", 3);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 7);
}
TEST_F(ApplicationServiceEnvironment, lock_amount) {
  init_fund("XX", 10);
  FundService::GetInstance()->LockAmount("XX", 3);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 7);
}
TEST_F(ApplicationServiceEnvironment, unlock_amount) {
  init_fund("XX", 10);
  FundService::GetInstance()->LockAmount("XX", 3);
  FundService::GetInstance()->UnLockAmount("XX", 1);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 8);
}
TEST_F(ApplicationServiceEnvironment, set_forbid_in) {
  FundService::GetInstance()->AddFundAccount("XX");
  FundService::GetInstance()->SetForbidIn("XX", true);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->forbid_in_, true);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->forbid_out_, false);
}
TEST_F(ApplicationServiceEnvironment, decrease_amount_after_set_forbid_in) {
  init_fund("XX", 10);
  FundService::GetInstance()->SetForbidIn("XX", true);
  FundService::GetInstance()->Decrease(1, "XX", 3);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 10);
}
TEST_F(ApplicationServiceEnvironment, set_forbid_out) {
  FundService::GetInstance()->AddFundAccount("XX");
  FundService::GetInstance()->SetForbidOut("XX", true);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->forbid_out_, true);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->forbid_in_, false);
}
TEST_F(ApplicationServiceEnvironment, increase_amount_after_set_forbid_out) {
  FundService::GetInstance()->AddFundAccount("XX");
  FundService::GetInstance()->Initialize("XX", 10);
  FundService::GetInstance()->SetForbidOut("XX", true);
  FundService::GetInstance()->Increase(1, "XX", 3);
  ASSERT_EQ(FundService::GetInstance()->GetFund("XX")->free_amount_, 10);
}
void add_fundPO(FundPO& fundPO_) {
  FundMenoryDAO* fundDao_ = FundMenoryDAO::BuildInstance();
  fundDao_->AddFundPO(fundPO_);
}
void check_fundPo_is_success(FundPO& fundPO_) {
  boost::optional<FundPO> result = FundMenoryDAO::BuildInstance()->GetFundPO(fundPO_.account_id_);
  ASSERT_EQ(result.has_value(), true);
  ASSERT_EQ(result.value().account_id_, fundPO_.account_id_);
  ASSERT_EQ(result.value().forbid_in_, fundPO_.forbid_in_);
  ASSERT_EQ(result.value().forbid_out_, fundPO_.forbid_out_);
  ASSERT_EQ(result.value().free_amount_, fundPO_.free_amount_);
  ASSERT_EQ(result.value().locked_amount_, fundPO_.locked_amount_);
}
void check_fundPo_is_fail(FundPO& fundPO_) {
  boost::optional<FundPO> result = FundMenoryDAO::BuildInstance()->GetFundPO(fundPO_.account_id_);
  ASSERT_EQ(result.has_value(), false);
}
TEST(DAO_test, add_fund) {
  FundPO fundPO_("XX", false, false, 10, 10);
  add_fundPO(fundPO_);
  check_fundPo_is_success(fundPO_);
  FundMenoryDAO::DestroyInstance();
}
TEST(DAO_test, update_fund_of_not_existed) {
  FundPO fundPO_1("XX", false, false, 10, 20);
  add_fundPO(fundPO_1);
  FundPO fundPOPO_2("YY", true, true, 20, 20);
  FundMenoryDAO::BuildInstance()->UpdateFundPO(fundPOPO_2);
  check_fundPo_is_fail(fundPOPO_2);
  FundMenoryDAO::DestroyInstance();
}
TEST(DAO_test, update_fund_of_existed) {
  FundPO fundPOPO_1("XX", false, false, 10, 20);
  add_fundPO(fundPOPO_1);
  FundPO fundPOPO_3("XX", true, true, 20, 20);
  FundMenoryDAO::BuildInstance()->UpdateFundPO(fundPOPO_3);
  check_fundPo_is_success(fundPOPO_3);
  FundMenoryDAO::DestroyInstance();
}
TEST(fund_domian_object, lock_when_amount_not_enough) {
  Fund fund("XX", false, false, 100, 0);
  fund.Lock_Amount(60);
  ASSERT_EQ(fund.Get_Free_Amount(), 40);
  ASSERT_EQ(fund.Get_Locked_Amount(), 60);
  ASSERT_EQ(fund.Get_Amount(), 100);
}
TEST(fund_domian_object, lock_when_amount_enough) {
  Fund fund("XX", false, false, 100, 0);
  bool result = fund.Lock_Amount(120);
  ASSERT_EQ(result, false);
  ASSERT_EQ(fund.Get_Free_Amount(), 100);
  ASSERT_EQ(fund.Get_Locked_Amount(), 0);
  ASSERT_EQ(fund.Get_Amount(), 100);
}
TEST(fund_domian_object, unlock_when_amount_enough) {
  Fund fund("XX", false, false, 50, 50);
  fund.UnLock_Amount(20);
  ASSERT_EQ(fund.Get_Free_Amount(), 70);
  ASSERT_EQ(fund.Get_Locked_Amount(), 30);
  ASSERT_EQ(fund.Get_Amount(), 100);
}
TEST(fund_domian_object, unlock_when_amount_not_enough) {
  Fund fund("XX", false, false, 50, 50);
  fund.UnLock_Amount(80);
  ASSERT_EQ(fund.Get_Free_Amount(), 100);
  ASSERT_EQ(fund.Get_Locked_Amount(), 0);
  ASSERT_EQ(fund.Get_Amount(), 100);
}
TEST_F(FundFrontendEnvironmentForCommand, FundHttpService_Lock_Amount) {
  LockAmountDTO lock_Amount_DTO("1", "XX", 10);
  HttpRequest httpRequest("", lock_Amount_DTO);
  FundHttpService::GetInstance()->LockAmount(httpRequest);
  ASSERT_EQ(FundServiceMock::GetInstance()->lock_Amount, true);
}
TEST_F(FundFrontendEnvironmentForCommand, FundHttpClient_Lock_Amount) {
  FundHttpClient::GetInstance()->LockAmount("XX", 10);
  ASSERT_EQ(FundServiceMock::GetInstance()->lock_Amount, true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}