#ifndef TRANSFER_查询服务_H
#define TRANSFER_查询服务_H
#include "../Application/TransferRepositoryInterface.h"
#include "../Application/TransferQueryInterface.h"
#include "TransferDAOInterface.h"
#include "TransferPO.h"
#include "../Domain/TransferUser.h"
#include "UserHttpClient.h"
class TransferQuery: public TransferQueryInterface{
private:
    UserServiceInterface * 用户服务接口_;
    TransferDAOInterface * 转账DAO接口_;
    TransferQuery(TransferDAOInterface* 转账DAO接口, UserServiceInterface * 用户服务接口): 转账DAO接口_(转账DAO接口), 用户服务接口_(用户服务接口){}
    static TransferQuery* 转账查询_;
public:
    virtual boost::optional<Transfer> 获取转账(int 单号) override {
        boost::optional<TransferPO> 转账PO_=转账DAO接口_->获取转账PO(单号);
        if(转账PO_.has_value()){
            return Transfer::构造旧的转账(转账PO_.value().单号,
                                    TransferUser(转账PO_.value().付款方账号,
                                                 用户服务接口_->是否已冻结(转账PO_.value().付款方账号)),
                                    TransferUser(转账PO_.value().收款方账号,
                                                 用户服务接口_->是否已冻结(转账PO_.value().收款方账号)),
                                    转账PO_.value().金额,
                                    Transfer::状态(转账PO_.value().状态));
        }
        return boost::none;
    }
    ~TransferQuery() {
        TransferQuery::转账查询_= nullptr;
    }
    static TransferQuery* 构建单例(TransferDAOInterface* 转账DAO接口, UserServiceInterface * 用户服务接口){
        if (TransferQuery::转账查询_ == nullptr) {
            TransferQuery::转账查询_ = new TransferQuery(转账DAO接口, 用户服务接口);
        }
        return TransferQuery::转账查询_;
    }
    static TransferQuery* 获取单例(){
        if(TransferQuery::转账查询_ == nullptr){
            throw "单例未创建";
        }
        return TransferQuery::转账查询_;
    }
    static void 销毁单例(){
        if(TransferQuery::转账查询_ != nullptr)
          delete TransferQuery::转账查询_;
    }
};


#endif //TRANSFER_查询服务_H
