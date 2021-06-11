#ifndef TRANSFER_TransferDAOMock_H
#define TRANSFER_TransferDAOMock_H
#include "../../../../src/bc/transfer/backend_adapters/transfer_po.h"
#include "../../../../src/bc/transfer/backend_adapters/transfer_dao_interface.h"
class TransferDAOMock: public TransferDAOInterface{
private:
    std::vector<TransferPO> transfers_;
    static TransferDAOMock* transferDAOMock;
    TransferDAOMock() {}
public:
    ~TransferDAOMock() {
        TransferDAOMock::transferDAOMock= nullptr;
        transfers_.clear();
    }
    static TransferDAOMock* GetInstance(){
        if (transferDAOMock == nullptr) {
            transferDAOMock = new TransferDAOMock();
        }
        return transferDAOMock;
    }
    virtual void AddTransferPO(const TransferPO &transferPO) override{
        transfers_.push_back(transferPO);
    }
    virtual boost::optional<TransferPO> GetTransferPO(int order_no) override{
        for(TransferPO transferPO_: transfers_){
           if(transferPO_.order_no_ == order_no){
               return transferPO_;
           }
        }
        return boost::none;
    };
    virtual void UpdateTransferPOStatus(int order_no,int status) override{
        for(TransferPO& transferPO_: transfers_){
            if(transferPO_.order_no_ == order_no){
                transferPO_.status_=status;
            }
        }
    };
};


#endif //TRANSFER_TransferDAOMock_H
