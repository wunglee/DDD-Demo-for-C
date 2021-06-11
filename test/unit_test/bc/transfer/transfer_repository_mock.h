#ifndef TRANSFER_TransferRepositoryMock_H
#define TRANSFER_TransferRepositoryMock_H
#include "../../../../src/global_business_dependency/service_interfaces/user/user_service_interface.h"
#include "../../../../src/bc/transfer/application/transfer_repository_interface.h"
#include "../../../../src/bc/transfer/domain/transfer.h"
#include "../../../../src/bc/transfer/domain/transfer_user.h"

class TransferRepositoryMock : public TransferRepositoryInterface{
private:
    std::vector<Transfer> &transfers_;
    UserServiceInterface* userServiceInterface_;
    static TransferRepositoryMock * transferRepositoryMock_;
    TransferRepositoryMock(std::vector<Transfer> &transfers, UserServiceInterface* userServiceInterface):
            transfers_(transfers), userServiceInterface_(userServiceInterface){
    }
    Transfer Get_New_Status_Transfer(int order_no, Transfer::Status status){
        for(Transfer &transfer:transfers_){
            if(transfer.GetOrderNo() == order_no){
                return Transfer::BuildOld(transfer.GetOrderNo(),
                                          TransferUser(transfer.GetPayerAccountId(),
                                                       userServiceInterface_->IsFrozen(
                                                               transfer.GetPayerAccountId())),
                                          TransferUser(transfer.GetPayeeAccountId(),
                                                       userServiceInterface_->IsFrozen(
                                                               transfer.GetPayeeAccountId())),
                                          transfer.GetAmount(), status);
            }
        }
        throw new Exception("没有找到");
    }
public:
    ~TransferRepositoryMock() {
        TransferRepositoryMock::transferRepositoryMock_= nullptr;
    }
    static TransferRepositoryMock* BuildInstance(std::vector<Transfer> &transfers_, UserServiceInterface* userServiceInterface_){
        if (transferRepositoryMock_ == nullptr) {
            transferRepositoryMock_ = new TransferRepositoryMock(transfers_, userServiceInterface_);
        }
        return transferRepositoryMock_;
    }
    static TransferRepositoryMock* GetInstance(){
        if(transferRepositoryMock_!= nullptr){
          return transferRepositoryMock_;
        }else{
            throw "单例未创建";
        }
    }
    void AddTransfer(const Transfer& transfer) override {
        transfers_.push_back(transfer);
    }

    Transfer GetExistedTransfer(int order_no) override {
        for(Transfer &transfer:transfers_){
            if(transfer.GetOrderNo() == order_no){
                return Transfer::BuildOld(transfer.GetOrderNo(),
                                          TransferUser(transfer.GetPayerAccountId(),
                                                       userServiceInterface_->IsFrozen(
                                                               transfer.GetPayerAccountId())),
                                          TransferUser(transfer.GetPayeeAccountId(),
                                                       userServiceInterface_->IsFrozen(
                                                               transfer.GetPayeeAccountId())),
                                          transfer.GetAmount(), transfer.GetStatus());
            }
        }
        throw new Exception("没有找到");
    }
    void UpdateTransferStatus(Transfer &transfer) override{
        Transfer new_status_transfer=Get_New_Status_Transfer(transfer.GetOrderNo(), transfer.GetStatus());
        transfers_.clear();
//        for(auto it=transfers_.begin();it!=transfers_.end();)
//        {
//            if(it->GetOrderNo() == order_no_) {
//                transfers_.erase(it);
//                break;
//            }
//            ++it;
//        }
        transfers_.push_back(new_status_transfer);
    }
};


#endif //TRANSFER_TransferRepositoryMock_H
