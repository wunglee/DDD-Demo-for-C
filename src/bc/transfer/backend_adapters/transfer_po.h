#ifndef TRANSFER_TransferPO_H
#define TRANSFER_TransferPO_H

class TransferPO {
 public:
  long order_no_;
  std::string payer_account_id_;
  std::string payee_account_id_;
  int status_;
  float amount_;
  TransferPO(
      long id,
      const std::string payer_account_id,
      const std::string payee_account_id,
      int status,
      float amount)
      : order_no_(id),
        payer_account_id_(payer_account_id),
        payee_account_id_(payee_account_id),
        status_(status),
        amount_(amount) {}
};

#endif  // TRANSFER_TransferPO_H
