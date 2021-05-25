#ifndef TRANSFER_资金帐户DAO_H
#define TRANSFER_资金帐户DAO_H
#include "FundDAOInterface.h"
class FundDAO: public FundDAOInterface {
private:
    static FundDAO* 资金帐户DAO_;
    std::vector<FundPO> 资金帐户集合_;
public:
    virtual ~FundDAO() {
        FundDAO::资金帐户DAO_= nullptr;
        资金帐户集合_.clear();
    }
    static FundDAO* 构建单例(){
        if (FundDAO::资金帐户DAO_ == nullptr) {
            FundDAO::资金帐户DAO_ = new FundDAO();
        }
        return FundDAO::资金帐户DAO_;
    }
    static FundDAO* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(FundDAO::资金帐户DAO_ != nullptr)
          delete FundDAO::资金帐户DAO_;
    }
    virtual void 新增资金帐户PO(const FundPO& 资金帐户PO) override {
        资金帐户集合_.push_back(资金帐户PO);
    };
    virtual void 更新资金帐户PO(const FundPO& _资金帐户PO) override{
        for(FundPO& 资金帐户PO_:资金帐户集合_){
            if(资金帐户PO_.账号 == _资金帐户PO.账号){
                资金帐户PO_.金额_=_资金帐户PO.金额_;
                资金帐户PO_.禁止转入_=_资金帐户PO.禁止转入_;
                资金帐户PO_.禁止转出_=_资金帐户PO.禁止转出_;
            }
        }
    } ;
    virtual boost::optional<FundPO>  获取资金帐户PO(const std::string 账号) override{
        for(FundPO& 资金帐户PO_:资金帐户集合_){
            if(资金帐户PO_.账号 == 账号){
               return 资金帐户PO_;
            }
        }
        return boost::none;
    }
};
#endif //TRANSFER_资金帐户DAO_H
