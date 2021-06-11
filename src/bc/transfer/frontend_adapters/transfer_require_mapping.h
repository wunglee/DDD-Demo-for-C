#ifndef TRANSFER_TransferRequireMapping_H
#define TRANSFER_TransferRequireMapping_H

#include "boost/any.hpp"

#include "../../../framework_components/naming_service/naming_service_manager.h"
#include "../../../framework_components/requestion_filters/require_mapping.h"
#include "../../../framework_components/requestion_filters/response.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_dto.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_service_interface.h"

class TransferRequireMapping : public RequireMapping {
 private:
  TransferServiceInterface* transferServiceInterface_;
  static TransferRequireMapping* transferRequireMapping_;

  TransferRequireMapping(TransferServiceInterface* transferServiceInterface_)
      : transferServiceInterface_(transferServiceInterface_) {}

 public:
  virtual ~TransferRequireMapping() { TransferRequireMapping::transferRequireMapping_ = nullptr; }

  static TransferRequireMapping* BuildInstance(
      TransferServiceInterface* transfer_service_interface) {
    if (TransferRequireMapping::transferRequireMapping_ == nullptr) {
      TransferRequireMapping::transferRequireMapping_ =
          new TransferRequireMapping(transfer_service_interface);
    }
    return TransferRequireMapping::transferRequireMapping_;
  }

  static TransferRequireMapping* GetInstance() {
    if (TransferRequireMapping::transferRequireMapping_ == nullptr) {
      throw "单例未构建";
    }
    return TransferRequireMapping::transferRequireMapping_;
  }

  static void DestroyInstance() {
    if (TransferRequireMapping::transferRequireMapping_ != nullptr) {
      delete TransferRequireMapping::transferRequireMapping_;
    }
  }

  virtual Response handle(std::string function_name, const boost::any& parameters) override {
    Response response;
    try {
      if (function_name == "ApplyTransfer") {
        ApplyTransferDTO apply_transfer_dto_ = boost::any_cast<ApplyTransferDTO>(parameters);
        int id = transferServiceInterface_->ApplyTransfer(
            apply_transfer_dto_.payer_account_,
            apply_transfer_dto_.payee_account_,
            apply_transfer_dto_.amount_);
        response.value = id;
      }
      if (function_name == "NotifyPayerFundDeducted") {
        int id = boost::any_cast<int>(parameters);
        transferServiceInterface_->NotifyPayerFundDeducted(id);
      }
      if (function_name == "NotifyCancel") {
        DecreaseFailDTO subAmountFailDTO = boost::any_cast<DecreaseFailDTO>(parameters);
        transferServiceInterface_->NotifyCancel(
            subAmountFailDTO.order_no_, subAmountFailDTO.exception_);
      }
      if (function_name == "NotifyApplyRefund") {
        IncreaseFailDTO addAmountFailDTO = boost::any_cast<IncreaseFailDTO>(parameters);
        transferServiceInterface_->NotifyApplyRefund(
            addAmountFailDTO.order_no_, addAmountFailDTO.exception_);
      }
      if (function_name == "NotifyFundIncreased") {
        IncreaseSuccessDTO addAmountSuccessDTO = boost::any_cast<IncreaseSuccessDTO>(parameters);
        transferServiceInterface_->NotifyFundIncreased(
            addAmountSuccessDTO.order_no_, addAmountSuccessDTO.account_id_);
      }
    } catch (Exception e) {
      response.exception = std::make_shared<Exception>(e);
    }
    return response;
  }
};

#endif  // TRANSFER_TransferRequireMapping_H
