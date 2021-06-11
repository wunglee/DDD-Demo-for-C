#pragma once
#include "transfer_service_interface.h"
class TransferServiceMock : public TransferServiceInterface {
 private:
  TransferServiceMock() {}
  static TransferServiceMock* tansfer_service_mock_;

 public:
  ~TransferServiceMock() { TransferServiceMock::tansfer_service_mock_ = nullptr; }
  static TransferServiceMock* GetInstance() {
    if (tansfer_service_mock_ == nullptr) {
      static TransferServiceMock tansfer_service_mock;
      tansfer_service_mock_ = &tansfer_service_mock;
    }
    return tansfer_service_mock_;
  }

  bool apply_transfer_called = false;
  bool notify_refund_called = false;
  bool notify_transfer_in_called = false;
  bool notify_cancel_called = false;
  bool notify_apply_refund_called = false;
  bool notify_transfer_out_called = false;

  int ApplyTransfer(
      std::string payor_account_id,
      std::string payee_account_id,
      float amount,
      int& order_no) override {
    apply_transfer_called = true;
    return 0;
  };
  int NotifyTransferIn(int order_no, std::string account_id) override {
    if (account_id == "XX") {
      notify_refund_called = true;
    }
    if (account_id == "YY") {
      notify_transfer_in_called = true;
    }
    return 0;
  };
  int NotifyCancel(int order_no) override {
    notify_cancel_called = true;
    return 0;
  };
  int NotifyApplyRefund(int order_no) override {
    notify_apply_refund_called = true;
    return 0;
  };
  int NotifyTransferOut(int order_no) override {
    notify_transfer_out_called = true;
    return 0;
  };
  int GetTransfer(int order_no, TransferDTO& dto) override { return -1000; }
};
