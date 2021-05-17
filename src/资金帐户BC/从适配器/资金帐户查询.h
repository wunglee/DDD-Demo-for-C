#ifndef TRANSFER_资金帐户查询_H
#define TRANSFER_资金帐户查询_H
#include "../应用层/资金帐户查询接口.h"
#include "资金帐户PO.h"
#include "资金帐户DAO接口.h"
class 资金帐户查询 : public 资金帐户查询接口 {
private:
    资金帐户DAO接口 * 资金帐户DAO接口_;
    static 资金帐户查询* 资金帐户查询服务_;
    资金帐户查询(资金帐户DAO接口 * 资金帐户DAO接口): 资金帐户DAO接口_(资金帐户DAO接口) {}
public:
    virtual ~资金帐户查询() {
        资金帐户查询::资金帐户查询服务_= nullptr;
    }
    static 资金帐户查询* 构建单例(资金帐户DAO接口 * 资金帐户DAO接口_){
        if (资金帐户查询::资金帐户查询服务_ == nullptr) {
            资金帐户查询::资金帐户查询服务_ = new 资金帐户查询(资金帐户DAO接口_);
        }
        return 资金帐户查询::资金帐户查询服务_;
    }
    static 资金帐户查询* 获取单例(){
        if(资金帐户查询::资金帐户查询服务_== nullptr){
            throw "单例未创建";
        }
        return 资金帐户查询::资金帐户查询服务_;
    }
    static void 销毁单例(){
        if(资金帐户查询::资金帐户查询服务_!= nullptr)
           delete 资金帐户查询::资金帐户查询服务_;
    }
    virtual boost::optional<资金帐户> 获取资金帐户(std::string 账号) override{
        boost::optional<资金帐户PO>  资金帐户PO_ = 资金帐户DAO接口_->获取资金帐户PO(账号);
        if(资金帐户PO_.has_value()){
                return 资金帐户(资金帐户PO_.value().账号,
                            资金帐户PO_.value().禁止转出_,
                            资金帐户PO_.value().禁止转入_,
                            资金帐户PO_.value().金额_);
        }
        return boost::none;
    }
};
#endif //TRANSFER_资金帐户查询_H
