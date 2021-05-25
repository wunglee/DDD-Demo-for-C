#ifndef TRANSFER_资金帐户仓储_H
#define TRANSFER_资金帐户仓储_H
#include "../Application/FundRepositoryInterface.h"
#include "FundPO.h"
#include "FundDAOInterface.h"
#include "FundQuery.h"
class FundRepository : public FundRepositoryInterface{
private:
    FundDAOInterface * 资金帐户DAO接口_;
    static FundRepository* 资金帐户仓储_;
    FundRepository(FundDAOInterface * 资金帐户DAO接口): 资金帐户DAO接口_(资金帐户DAO接口) {}
public:
    virtual ~FundRepository() {
        FundRepository::资金帐户仓储_= nullptr;
    }
    static FundRepository* 构建单例(FundDAOInterface * 资金帐户DAO接口_){
        assert(资金帐户DAO接口_!= nullptr);
        if (FundRepository::资金帐户仓储_ == nullptr) {
            FundRepository::资金帐户仓储_ = new FundRepository(资金帐户DAO接口_);
        }
        return FundRepository::资金帐户仓储_;
    }
    static FundRepository* 获取单例(){
        if(FundRepository::资金帐户仓储_ == nullptr){
            throw "单例未创建";
        }
        return FundRepository::资金帐户仓储_;
    }
    static void 销毁单例(){
        if(FundRepository::资金帐户仓储_ != nullptr)
          delete FundRepository::资金帐户仓储_;
    }
    virtual Fund 获取必须存在的资金帐户(std::string 账号)override{
        boost::optional<Fund> 资金帐户_=FundQuery::获取单例()->获取资金帐户(账号);
        if(!资金帐户_.has_value()){
            throw Exception((boost::format("没有找到资金帐户:%1%") % 账号).str());
        }
        return 资金帐户_.value();
    }
    virtual void 新增资金帐户(Fund& 资金帐户) override{
        FundPO 资金帐户PO_(资金帐户.获取账号(), 资金帐户.是否禁止转出(), 资金帐户.是否禁止转入(), 资金帐户.获取金额());
        资金帐户DAO接口_->新增资金帐户PO(资金帐户PO_);
    }
    virtual void 更新资金帐户(Fund& 资金帐户) override{
        FundPO 资金帐户PO_(资金帐户.获取账号(), 资金帐户.是否禁止转出(), 资金帐户.是否禁止转入(), 资金帐户.获取金额());
        资金帐户DAO接口_->更新资金帐户PO(资金帐户PO_);
    }
};


#endif //TRANSFER_资金帐户仓储_H
