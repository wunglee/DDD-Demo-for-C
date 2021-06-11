#ifndef TRANSFER_TransferServiceInterface_H
#define TRANSFER_TransferServiceInterface_H
#include <string>
#include "boost/optional.hpp"
#include "../../../framework_components/exception.h"
#include "../../../bc/transfer/domain/transfer.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_dto.h"
class TransferServiceInterface {
public:
    virtual ~TransferServiceInterface() {
    }
    virtual int ApplyTransfer(std::string payer_acount_id, std::string payee_acount_id, float amount)=0;
    virtual void NotifyFundIncreased(int order_no, std::string account_id)=0;
    virtual void NotifyCancel(int order_no, Exception Exception)=0;
    virtual void NotifyApplyRefund(int order_no, Exception exception)=0;
    virtual void NotifyPayerFundDeducted(int order_no)=0;
    virtual boost::optional<TransferDTO> GetTransfer(int order_no)=0;
};


#endif //TRANSFER_TransferServiceInterface_H
