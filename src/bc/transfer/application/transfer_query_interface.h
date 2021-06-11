#ifndef TRANSFER_TransferQueryInterface_H
#define TRANSFER_TransferQueryInterface_H


class TransferQueryInterface {
public:
    virtual ~TransferQueryInterface() {}
    virtual boost::optional<Transfer> Get_Transfer(int order_id)=0;
};


#endif //TRANSFER_TransferQueryInterface_H
