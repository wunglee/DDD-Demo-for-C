#ifndef TRANSFER_TransferDAOInterface_H
#define TRANSFER_TransferDAOInterface_H
#include "boost/optional.hpp"
#include "transfer_po.h"
class TransferDAOInterface {
public:
    virtual ~TransferDAOInterface(){}
    virtual void AddTransferPO(const TransferPO &transferPO)=0;
    virtual boost::optional<TransferPO> GetTransferPO(int id)=0;
    virtual void UpdateTransferPOStatus(int id, int status)=0;
};


#endif //TRANSFER_TransferDAOInterface_H
