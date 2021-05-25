#ifndef TRANSFER_转账仓储_H
#define TRANSFER_转账仓储_H
#include "../Application/TransferRepositoryInterface.h"
#include "TransferPO.h"
#include "TransferDAOInterface.h"
#include "UserHttpClient.h"
class TransferRepository : public TransferRepositoryInterface{
private:
    UserServiceInterface * 用户服务接口_;
    TransferDAOInterface * 转账DAO接口_;
    static TransferRepository* 转账仓储_;
    TransferRepository(TransferDAOInterface* 转账DAO接口, UserServiceInterface *用户服务接口): 转账DAO接口_(转账DAO接口), 用户服务接口_(用户服务接口) {}
public:
    ~TransferRepository() {
        TransferRepository::转账仓储_= nullptr;
    }
    static TransferRepository* 构建单例(TransferDAOInterface * 转账DAO接口_, UserServiceInterface *用户服务接口){
        if (TransferRepository::转账仓储_ == nullptr) {
            TransferRepository::转账仓储_ = new TransferRepository(转账DAO接口_, 用户服务接口);
        }
        return TransferRepository::转账仓储_;
    }
    static TransferRepository* 获取单例(){
        if(TransferRepository::转账仓储_ == nullptr){
            throw "单例未创建";
        }
        return TransferRepository::转账仓储_;
    }
    static void 销毁单例(){
        if(TransferRepository::转账仓储_ != nullptr)
          delete TransferRepository::转账仓储_;
    }
    virtual void 新增转账(const Transfer& 转账_) override{
        TransferPO 转账PO(转账_.获取单号(),
                        转账_.获取付款方账号(),
                        转账_.获取收款方账号(),
                        转账_.获取状态(),
                        转账_.获取金额());
        转账DAO接口_->新增转账PO(转账PO);
    }
    virtual Transfer 获取必须存在的转账(int 单号) override{
        boost::optional<TransferPO> 转账PO_=转账DAO接口_->获取转账PO(单号);
        if(转账PO_.has_value()){
            if(转账PO_.value().单号 == 单号){
                return Transfer::构造旧的转账(转账PO_.value().单号,
                                        TransferUser(转账PO_.value().付款方账号,
                                                     用户服务接口_->是否已冻结(转账PO_.value().付款方账号)),
                                        TransferUser(转账PO_.value().收款方账号,
                                                     用户服务接口_->是否已冻结(转账PO_.value().收款方账号)),
                                        转账PO_.value().金额,
                                        Transfer::状态(转账PO_.value().状态));
            }
        }
        throw Exception((boost::format("没有找到转账单:%1%") % 单号).str());;
    }
    virtual void 更新转账状态(int 单号, Transfer::状态 状态) override{
        转账DAO接口_->更新转账PO状态(单号,状态);
    }
};


#endif //TRANSFER_转账仓储_H
