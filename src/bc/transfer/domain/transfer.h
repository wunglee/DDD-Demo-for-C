#ifndef ARGS_Transfer_H
#define ARGS_Transfer_H
#include <boost/format.hpp>

#include "../../../framework_components/exception.h"
#include "transfer_user.h"
class Transfer {
 public:
  enum Status { Created, Canceled, Payer_Deducted, Payee_Increased, Applying_Refund, Refunded };

 private:
  int order_no_;
  TransferUser payer;
  TransferUser payee;
  Status status;
  float amount;
  void Check_User(TransferUser& transferUser) {
    if (transferUser.frozen_) {
      throw Exception((boost::format("帐户已经冻结:%s") % transferUser.acount_id_).str());
    }
  }
  Transfer(
      TransferUser& payer,
      TransferUser& payee,
      float amount,
      Transfer::Status status = Created,
      int order_no = rand())
      : order_no_(order_no), payer(payer), payee(payee), status(status), amount(amount) {
    Check_User(payer);
    Check_User(payee);
  }

 public:
  static Transfer CreateNew(TransferUser payer, TransferUser payee, float amount) {
    return Transfer(payer, payee, amount);
  }
  static Transfer BuildOld(
      int id, TransferUser payer, TransferUser payee, float ammout, Status status) {
    return Transfer(payer, payee, ammout, status, id);
  }
  int GetOrderNo() const { return order_no_; }
  std::string GetPayerAccountId() const { return payer.acount_id_; }
  const std::string GetPayeeAccountId() const { return payee.acount_id_; }
  Status GetStatus() const { return status; }
  void PayerFundDeducted() {
    if (status == Created) {
      status = Payer_Deducted;
    } else {
      throw Exception("状态不在申请中状态，无法设置已出账状态");
    }
  }
  void PayeeFundIncreased() {
    if (status == Payer_Deducted) {
      status = Payee_Increased;
    } else {
      throw Exception("状态不在付款出账中状态，无法设置已到账状态");
    }
  }
  void Cancel(Exception cancel_season) {
    if (status == Created) {
      status = Canceled;
    } else {
      throw Exception("状态不在申请中状态，无法取消");
    }
  }
  void ApplyRefund(Exception refund_reason) {
    if (status == Payer_Deducted) {
      status = Applying_Refund;
    } else {
      throw Exception("状态不在付款出账中状态，无法设置退款中状态");
    }
  }
  void RefundFinshed() {
    if (status == Applying_Refund) {
      status = Refunded;
    } else {
      throw Exception("状态不在付款退款中状态，无法设置已退回状态");
    }
  }
  float GetAmount() const { return amount; }
};
#endif  // ARGS_Transfer_H
