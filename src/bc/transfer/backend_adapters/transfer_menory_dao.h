#ifndef TRANSFER_TransferDAO_H
#define TRANSFER_TransferDAO_H
#include "transfer_dao_interface.h"
#include "transfer_po.h"
class TransferMenoryDAO: public TransferDAOInterface{
private:
    std::vector<TransferPO> transfers_;
    static TransferMenoryDAO* transfer_dao_;
    TransferMenoryDAO() {}
public:
    ~TransferMenoryDAO() {
        TransferMenoryDAO::transfer_dao_= nullptr;
        transfers_.clear();
    }
    static TransferMenoryDAO* BuildInstance(){
        if (TransferMenoryDAO::transfer_dao_ == nullptr) {
            TransferMenoryDAO::transfer_dao_ = new TransferMenoryDAO();
        }
        return TransferMenoryDAO::transfer_dao_;
    }
    static TransferMenoryDAO * GetInstance(){
        return BuildInstance();
    }
    static void DestroyInstance(){
        if(TransferMenoryDAO::transfer_dao_ != nullptr)
           delete TransferMenoryDAO::transfer_dao_;
    }
    virtual void AddTransferPO(const TransferPO &transferPO) override{
        transfers_.push_back(transferPO);
    }
    virtual boost::optional<TransferPO> GetTransferPO(int id) override{
        for(TransferPO transferPO_: transfers_){
           if(transferPO_.order_no_ == id){
               return transferPO_;
           }
        }
        return boost::none;
    };
    virtual void UpdateTransferPOStatus(int id, int status) override{
        for(TransferPO& transferPO_: transfers_){
            if(transferPO_.order_no_ == id){
                transferPO_.status_=status;
            }
        }
    };
};


#endif //TRANSFER_TransferDAO_H
