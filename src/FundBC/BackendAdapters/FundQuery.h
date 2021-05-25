#ifndef TRANSFER_资金帐户查询_H
#define TRANSFER_资金帐户查询_H
#include "../Application/FundServiceQueryInterface.h"
#include "FundPO.h"
#include "FundDAOInterface.h"
class FundQuery : public FundServiceQueryInterface {
private:
    FundDAOInterface * 资金帐户DAO接口_;
    static FundQuery* 资金帐户查询服务_;
    FundQuery(FundDAOInterface * 资金帐户DAO接口): 资金帐户DAO接口_(资金帐户DAO接口) {}
public:
    virtual ~FundQuery() {
        FundQuery::资金帐户查询服务_= nullptr;
    }
    static FundQuery* 构建单例(FundDAOInterface * 资金帐户DAO接口_){
        assert(资金帐户DAO接口_!= nullptr);
        if (FundQuery::资金帐户查询服务_ == nullptr) {
            FundQuery::资金帐户查询服务_ = new FundQuery(资金帐户DAO接口_);
        }
        return FundQuery::资金帐户查询服务_;
    }
    static FundQuery* 获取单例(){
        if(FundQuery::资金帐户查询服务_ == nullptr){
            throw "单例未创建";
        }
        return FundQuery::资金帐户查询服务_;
    }
    static void 销毁单例(){
        if(FundQuery::资金帐户查询服务_ != nullptr)
           delete FundQuery::资金帐户查询服务_;
    }
    virtual boost::optional<Fund> 获取资金帐户(std::string 账号) override{
        boost::optional<FundPO>  资金帐户PO_ = 资金帐户DAO接口_->获取资金帐户PO(账号);
        if(资金帐户PO_.has_value()){
                return Fund(资金帐户PO_.value().账号,
                            资金帐户PO_.value().禁止转出_,
                            资金帐户PO_.value().禁止转入_,
                            资金帐户PO_.value().金额_);
        }
        return boost::none;
    }
};
#endif //TRANSFER_资金帐户查询_H
