#ifndef TRANSFER_TransferQueryMock_H
#define TRANSFER_TransferQueryMock_H
#include "../../../../src/bc/transfer/application/transfer_query_interface.h"
class TransferQueryMock: public TransferQueryInterface {
    std::vector<Transfer> &transfers_;
    static TransferQueryMock* transferQueryMock_;
    TransferQueryMock(std::vector<Transfer> &transfers): transfers_(transfers){
    }
public:
    ~TransferQueryMock() {
        TransferQueryMock::transferQueryMock_= nullptr;
    }
    static TransferQueryMock* GetInstance(std::vector<Transfer> &transfers_){
        if (transferQueryMock_ == nullptr) {
            transferQueryMock_ = new TransferQueryMock(transfers_);
        }
        return transferQueryMock_;
    }
    boost::optional<Transfer> Get_Transfer(int order_no) override {
        for(Transfer& transfer:transfers_){
            if(transfer.GetOrderNo() == order_no){
                return transfer;
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_TransferQueryMock_H
