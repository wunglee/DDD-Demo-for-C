#ifndef TRANSFER_TransferRepository_H
#define TRANSFER_TransferRepository_H
#include "../../../global_business_dependency/service_interfaces/user/user_http_client.h"
#include "../application/transfer_repository_interface.h"
#include "transfer_dao_interface.h"
#include "transfer_po.h"
class TransferRepository : public TransferRepositoryInterface {
 private:
  TransferDAOInterface* transferDAOInterface_;
  UserServiceInterface* userServiceInterface_;
  static TransferRepository* transferRepository_;
  TransferRepository(
      TransferDAOInterface* transferDAOInterface, UserServiceInterface* userServiceInterface)
      : transferDAOInterface_(transferDAOInterface), userServiceInterface_(userServiceInterface) {}

 public:
  ~TransferRepository() { TransferRepository::transferRepository_ = nullptr; }
  static TransferRepository* BuildInstance(
      TransferDAOInterface* transferDAOInterface_, UserServiceInterface* userServiceInterface) {
    if (TransferRepository::transferRepository_ == nullptr) {
      TransferRepository::transferRepository_ =
          new TransferRepository(transferDAOInterface_, userServiceInterface);
    }
    return TransferRepository::transferRepository_;
  }
  static TransferRepository* GetInstance() {
    if (TransferRepository::transferRepository_ == nullptr) {
      throw "单例未创建";
    }
    return TransferRepository::transferRepository_;
  }
  static void DestroyInstance() {
    if (TransferRepository::transferRepository_ != nullptr)
      delete TransferRepository::transferRepository_;
  }
  virtual void AddTransfer(const Transfer& transfer) override {
    TransferPO transferPO(
        transfer.GetOrderNo(),
        transfer.GetPayerAccountId(),
        transfer.GetPayeeAccountId(),
        transfer.GetStatus(),
        transfer.GetAmount());
    transferDAOInterface_->AddTransferPO(transferPO);
  }
  virtual Transfer GetExistedTransfer(int order_no) override {
    boost::optional<TransferPO> transferPO_ = transferDAOInterface_->GetTransferPO(order_no);
    if (transferPO_.has_value()) {
      if (transferPO_.value().order_no_ == order_no) {
        return Transfer::BuildOld(
            transferPO_.value().order_no_,
            TransferUser(
                transferPO_.value().payer_account_id_,
                userServiceInterface_->IsFrozen(transferPO_.value().payer_account_id_)),
            TransferUser(
                transferPO_.value().payee_account_id_,
                userServiceInterface_->IsFrozen(transferPO_.value().payee_account_id_)),
            transferPO_.value().amount_,
            Transfer::Status(transferPO_.value().status_));
      }
    }
    throw Exception((boost::format("没有找到转账单:%1%") % order_no).str());
    ;
  }

  void UpdateTransferStatus(Transfer& transfer) override {
    transferDAOInterface_->UpdateTransferPOStatus(transfer.GetOrderNo(), transfer.GetStatus());
  }
};

#endif  // TRANSFER_TransferRepository_H
