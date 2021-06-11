#ifndef TRANSFER_TransferQuery_H
#define TRANSFER_TransferQuery_H
#include "../../../global_business_dependency/service_interfaces/user/user_http_client.h"
#include "../application/transfer_query_interface.h"
#include "../application/transfer_repository_interface.h"
#include "../domain/transfer_user.h"
#include "transfer_dao_interface.h"
#include "transfer_po.h"
class TransferQuery : public TransferQueryInterface {
 private:
  TransferDAOInterface* transferDAOInterface_;
  UserServiceInterface* userServiceInterface_;
  TransferQuery(
      TransferDAOInterface* transferDAOInterface, UserServiceInterface* userServiceInterface)
      : transferDAOInterface_(transferDAOInterface), userServiceInterface_(userServiceInterface) {}
  static TransferQuery* transferQuery_;

 public:
  virtual boost::optional<Transfer> Get_Transfer(int id) override {
    boost::optional<TransferPO> transferPO_ = transferDAOInterface_->GetTransferPO(id);
    if (transferPO_.has_value()) {
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
    return boost::none;
  }
  ~TransferQuery() { TransferQuery::transferQuery_ = nullptr; }
  static TransferQuery* BuildInstance(
      TransferDAOInterface* transferDAOInterface, UserServiceInterface* userServiceInterface) {
    if (TransferQuery::transferQuery_ == nullptr) {
      TransferQuery::transferQuery_ = new TransferQuery(transferDAOInterface, userServiceInterface);
    }
    return TransferQuery::transferQuery_;
  }
  static TransferQuery* GetInstance() {
    if (TransferQuery::transferQuery_ == nullptr) {
      throw "单例未创建";
    }
    return TransferQuery::transferQuery_;
  }
  static void DestroyInstance() {
    if (TransferQuery::transferQuery_ != nullptr) delete TransferQuery::transferQuery_;
  }
};

#endif  // TRANSFER_TransferQuery_H
