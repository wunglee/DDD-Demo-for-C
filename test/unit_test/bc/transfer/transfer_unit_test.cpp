#include "gtest/gtest.h"

#include "../../../../src/bc/transfer/backend_adapters/transfer_menory_dao.h"
#include "../../../../src/bc/transfer/frontend_adapters/protobuf_require_adaptor.h"
#include "../../../common_test_funtions.h"
#include "application_test_environment.h"
#include "transfer_backend_environment.h"
#include "transfer_event_environment.h"
#include "transfer_frontend_environment.h"

int create_transfer(
    std::string payer_account_id,
    std::string payee_account_id,
    float amount,
    Transfer::Status status) {
  Transfer transfer = Transfer::BuildOld(
      rand(), TransferUser(payer_account_id), TransferUser(payee_account_id), amount, status);
  TransferRepositoryMock::GetInstance()->AddTransfer(transfer);
  return transfer.GetOrderNo();
}
TEST_F(ApplicationTestEnvironment, apply_transfer) {
  check_transfer(apply_transfer(userServiceInterface_, "XX", "YY", 100), Transfer::Created);
}
TEST_F(ApplicationTestEnvironment, create_transfer_when_amount_not_enough) {
  FundServiceRemoteMock::GetInstance()->setLockedfail();
  ASSERT_THROW(apply_transfer(userServiceInterface_, "XX", "YY", 100), Exception);
}
void aplly_transfer_when_account_frozen(
    UserServiceInterface* userServiceInterface_, bool payer_frozen, bool payee_frozen) {
  create_user(userServiceInterface_, "XX", payer_frozen, "YY", payee_frozen);
  TransferServiceInterface* transferServiceInterface =
      NamingServiceManager::GetInstance()
          ->Find_Service<TransferServiceInterface*>("TransferService")
          .value();
  ASSERT_THROW(transferServiceInterface->ApplyTransfer("XX", "YY", 100), Exception);
}
TEST_F(ApplicationTestEnvironment, apply_transfer_when_payer_frozen) {
  aplly_transfer_when_account_frozen(userServiceInterface_, true, false);
}
TEST_F(ApplicationTestEnvironment, apply_transfer_when_payee_frozen) {
  aplly_transfer_when_account_frozen(userServiceInterface_, false, true);
}
TransferServiceInterface* get_transfer_service() {
  return NamingServiceManager::GetInstance()
      ->Find_Service<TransferServiceInterface*>("TransferService")
      .value();
}
int inti_transfer(Transfer::Status status) { return create_transfer("XX", "YY", 100, status); }
TEST_F(ApplicationTestEnvironment, notify_payer_the_fund_deducted_after_transfer_created) {
  int order_no = inti_transfer(Transfer::Created);
  get_transfer_service()->NotifyPayerFundDeducted(order_no);
  check_transfer(order_no, Transfer::Payer_Deducted);
}
TEST_F(ApplicationTestEnvironment, notify_cancel_after_transfer_created) {
  int order_no = inti_transfer(Transfer::Created);
  get_transfer_service()->NotifyCancel(order_no, Exception(""));
  check_transfer(order_no, Transfer::Canceled);
}
TEST_F(ApplicationTestEnvironment, notify_payee_the_fund_increased_after_payer_deducted) {
  int order_no = inti_transfer(Transfer::Payer_Deducted);
  get_transfer_service()->NotifyFundIncreased(order_no, "YY");
  check_transfer(order_no, Transfer::Payee_Increased);
}
TEST_F(ApplicationTestEnvironment, payee_frozen_before_fund_increased) {
  create_user(userServiceInterface_, "XX", "YY");
  int order_no = inti_transfer(Transfer::Payer_Deducted);
  userServiceInterface_->FreezeUser("YY");
  ASSERT_THROW(get_transfer_service()->NotifyFundIncreased(order_no, "YY"), Exception);
}
TEST_F(ApplicationTestEnvironment, notify_apply_refund_after_payer_deducted) {
  int order_no = inti_transfer(Transfer::Transfer::Payer_Deducted);
  get_transfer_service()->NotifyApplyRefund(order_no, Exception(""));
  check_transfer(order_no, Transfer::Applying_Refund);
}
TEST_F(ApplicationTestEnvironment, notify_payer_the_fund_increased_after_applying_refund) {
  int order_no = inti_transfer(Transfer::Transfer::Applying_Refund);
  get_transfer_service()->NotifyFundIncreased(order_no, "XX");
  check_transfer(order_no, Transfer::Refunded);
}
TEST_F(TransferEventEnvironment, notify_transfer_canceled_after_sub_amount_fail) {
    PublishSubscribeService::BuildInstance()->Publish(
        DomainEvent("扣减已失败", 0, DecreaseFailDTO(0, Exception("failed")).Serialize()));
    ASSERT_EQ(TansferServiceMock::GetInstance()->notifyCancelExecuted, true);

}
TEST_F(TransferEventEnvironment, notify_payer_the_fund_deducted_after_sub_amount_success) {
  PublishSubscribeService::BuildInstance()->Publish(DomainEvent("扣减已成功", 0, ""));
  ASSERT_EQ(TansferServiceMock::GetInstance()->NotifyPayerFundDeductedExecuted, true);
}
TEST_F(TransferEventEnvironment, notify_payee_the_fund_increased_after_add_amount_success) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("增资已成功", 0, IncreaseSuccessDTO(0, "YY", 1).Serialize()));
  ASSERT_EQ(TansferServiceMock::GetInstance()->notifyPayeeFundIncreasedExecuted, true);
}
TEST_F(TransferEventEnvironment, notify_apply_refund_after_payee_amount_add_fail) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("增资已失败", 0, IncreaseFailDTO(0, Exception("failed")).Serialize()));
  ASSERT_EQ(TansferServiceMock::GetInstance()->notifyApplyRefundExecuted, true);
}
TEST_F(TransferEventEnvironment, notify_refund_complete_after_payer_amount_add_success) {
  PublishSubscribeService::BuildInstance()->Publish(
      DomainEvent("增资已成功", 0, IncreaseSuccessDTO(0, "XX", 1).Serialize()));
  ASSERT_EQ(TansferServiceMock::GetInstance()->notifyRefundExecuted, true);
}
Transfer repository_add_transfer(
    std::string payer_account_id, std::string payee_account_id, float amount) {
  TransferRepository* transferRepository_ = TransferRepository::GetInstance();
  Transfer transfer = Transfer::CreateNew(
      TransferUser(payer_account_id, false), TransferUser(payee_account_id, false), amount);
  transferRepository_->AddTransfer(transfer);
  return transfer;
}
TEST_F(TransferBackendEnvironment, repository_add_transfer) {
  Transfer transfer = repository_add_transfer("XX", "YY", 10);
  ASSERT_EQ(
      TransferRepository::GetInstance()->GetExistedTransfer(transfer.GetOrderNo()).GetStatus(),
      Transfer::Created);
}
TEST_F(TransferBackendEnvironment, repository_update_transfer_status) {
  Transfer transfer = repository_add_transfer("XX", "YY", 10);
  transfer.PayerFundDeducted();
  TransferRepository::GetInstance()->UpdateTransferStatus(transfer);
  ASSERT_EQ(
      TransferRepository::GetInstance()->GetExistedTransfer(transfer.GetOrderNo()).GetStatus(),
      Transfer::Payer_Deducted);
}
int addTransferFromDao(
    int order_no,
    std::string payer_account_id,
    std::string payee_account_id,
    float amount,
    int status) {
  TransferMenoryDAO* transfer_dao_ = TransferMenoryDAO::BuildInstance();
  TransferPO transferPO_(order_no, payer_account_id, payee_account_id, status, amount);
  transfer_dao_->AddTransferPO(transferPO_);
  return transferPO_.order_no_;
}
TEST(transfer_DAO_test, add) {
  int order_no = addTransferFromDao(1, "XX", "YY", 10, 0);
  TransferMenoryDAO* transfer_dao_ = TransferMenoryDAO::BuildInstance();
  ASSERT_EQ(transfer_dao_->GetTransferPO(order_no)->status_, 0);
}
TEST(transfer_DAO_test, UpdateTransferPOStatus) {
  int order_no = addTransferFromDao(1, "XX", "YY", 10, 0);
  TransferMenoryDAO* transfer_dao_ = TransferMenoryDAO::BuildInstance();
  transfer_dao_->UpdateTransferPOStatus(order_no, 2);
  ASSERT_EQ(transfer_dao_->GetTransferPO(order_no)->status_, 2);
}
TEST_F(TransferFrontendEnvironment, apply_transfer) {
  ProtobufRequireAdaptor* protobufRequireAdaptor_ =
      NamingServiceManager::GetInstance()
          ->Find_Service<ProtobufRequireAdaptor*>("ProtobufRequireAdaptor")
          .value();
  ApplyTransferDTO applyTransferDTO("XX", "YY", 10);
  protobufRequireAdaptor_->ApplyTransfer("1", applyTransferDTO);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}