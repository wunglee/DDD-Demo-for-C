#ifndef TRANSFER_Common_Test_Functions_H
#define TRANSFER_Common_Test_Functions_H
#include "../src/bc/transfer/application/transfer_service.h"
#include "../src/bc/transfer/domain/transfer.h"
#include "../src/global_business_dependency/service_interfaces/transfer/transfer_service_interface.h"
#include "../src/global_business_dependency/service_interfaces/user/user_service_interface.h"

void create_user(
    UserServiceInterface* userServiceInterface_,
    std::string payer_account_id,
    bool freeze_payer,
    std::string payee_account_id,
    bool freeze_payee) {
  userServiceInterface_->AddUser(payer_account_id);
  userServiceInterface_->AddUser(payee_account_id);
  if (freeze_payer) userServiceInterface_->FreezeUser(payer_account_id);
  if (freeze_payee) userServiceInterface_->FreezeUser(payee_account_id);
}
void create_user(
    UserServiceInterface* userServiceInterface_,
    std::string payer_account_id,
    std::string payee_account_id) {
  create_user(userServiceInterface_, payer_account_id, false, payee_account_id, false);
}
void init_fund_account(UserServiceInterface* userServiceInterface_) {
  PublishSubscribeService::BuildInstance()->Subscribe("用户已创建", "FundEventMonitor");
  create_user(userServiceInterface_, std::string("XX"), std::string("YY"));
}
void check_transfer(int order_no, Transfer::Status status) {
  boost::optional<TransferDTO> transfer = TransferService::GetInstance()->GetTransfer(order_no);
  ASSERT_EQ(transfer.has_value(), true);
  ASSERT_EQ(transfer.value().status_, status);
}
int apply_transfer(
    UserServiceInterface* userServiceInterface_,
    std::string payer_account_id,
    std::string payee_account_id,
    float amount) {
  create_user(userServiceInterface_, payer_account_id, payee_account_id);
  TransferServiceInterface* transferServiceInterface =
      NamingServiceManager::GetInstance()
          ->Find_Service<TransferServiceInterface*>("TransferService")
          .value();
  return transferServiceInterface->ApplyTransfer(payer_account_id, payee_account_id, amount);
}
#endif  // TRANSFER_Common_Test_Functions_H
