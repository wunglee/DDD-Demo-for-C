#ifndef TRANSFER_资金帐户仓储_H
#define TRANSFER_资金帐户仓储_H
#include "../应用层/资金帐户仓储接口.h"
#include "资金帐户PO.h"
#include "资金帐户DAO接口.h"
#include "资金帐户查询.h"
class 资金帐户仓储 : public 资金帐户仓储接口{
private:
    资金帐户DAO接口 * 资金帐户DAO接口_;
    static 资金帐户仓储* 资金帐户仓储_;
    资金帐户仓储(资金帐户DAO接口 * 资金帐户DAO接口):资金帐户DAO接口_(资金帐户DAO接口) {}
public:
    virtual ~资金帐户仓储() {
        资金帐户仓储::资金帐户仓储_= nullptr;
    }
    static 资金帐户仓储* 构建单例(资金帐户DAO接口 * 资金帐户DAO接口_){
        if (资金帐户仓储::资金帐户仓储_ == nullptr) {
            资金帐户仓储::资金帐户仓储_ = new 资金帐户仓储(资金帐户DAO接口_);
        }
        return 资金帐户仓储::资金帐户仓储_;
    }
    static 资金帐户仓储* 获取单例(){
        if(资金帐户仓储::资金帐户仓储_== nullptr){
            throw "单例未创建";
        }
        return 资金帐户仓储::资金帐户仓储_;
    }
    static void 销毁单例(){
        if(资金帐户仓储::资金帐户仓储_!= nullptr)
          delete 资金帐户仓储::资金帐户仓储_;
    }
    virtual 资金帐户 获取必须存在的资金帐户(std::string 账号)override{
        boost::optional<资金帐户> 资金帐户_=资金帐户查询::获取单例()->获取资金帐户(账号);
        if(!资金帐户_.has_value()){
            throw 异常((boost::format("没有找到资金帐户:%1%")%账号).str());
        }
        return 资金帐户_.value();
    }
    virtual void 新增资金帐户(资金帐户& 资金帐户) override{
        资金帐户PO 资金帐户PO_(资金帐户.获取账号(),资金帐户.是否禁止转出(),资金帐户.是否禁止转入(),资金帐户.获取金额());
        资金帐户DAO接口_->新增资金帐户PO(资金帐户PO_);
    }
    virtual void 更新资金帐户(资金帐户& 资金帐户) override{
        资金帐户PO 资金帐户PO_(资金帐户.获取账号(),资金帐户.是否禁止转出(),资金帐户.是否禁止转入(),资金帐户.获取金额());
        资金帐户DAO接口_->更新资金帐户PO(资金帐户PO_);
    }
};


#endif //TRANSFER_资金帐户仓储_H
