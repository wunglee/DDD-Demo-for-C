#ifndef TRANSFER_TransferRepositoryInterface_H
#define TRANSFER_TransferRepositoryInterface_H
#include "../domain/transfer.h"
#include "boost/optional.hpp"
class TransferRepositoryInterface {
public:
    virtual ~TransferRepositoryInterface(){}
    virtual void AddTransfer(const Transfer& transfer)=0;
    virtual Transfer GetExistedTransfer(int order_id)=0;
    virtual void UpdateTransferStatus(Transfer & transfer)=0;
};
#endif //TRANSFER_TransferRepositoryInterface_H
