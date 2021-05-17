#ifndef TRANSFER_资金帐户DAO_H
#define TRANSFER_资金帐户DAO_H
#include "资金帐户DAO接口.h"
class 资金帐户DAO: public 资金帐户DAO接口 {
private:
    static 资金帐户DAO* 资金帐户DAO_;
    std::vector<资金帐户PO> 资金帐户集合_;
public:
    virtual ~资金帐户DAO() {
        资金帐户DAO::资金帐户DAO_= nullptr;
        资金帐户集合_.clear();
    }
    static 资金帐户DAO* 构建单例(){
        if (资金帐户DAO::资金帐户DAO_ == nullptr) {
            资金帐户DAO::资金帐户DAO_ = new 资金帐户DAO();
        }
        return 资金帐户DAO::资金帐户DAO_;
    }
    static 资金帐户DAO* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(资金帐户DAO::资金帐户DAO_!= nullptr)
          delete 资金帐户DAO::资金帐户DAO_;
    }
    virtual void 新增资金帐户PO(const 资金帐户PO& 资金帐户PO) override {
        资金帐户集合_.push_back(资金帐户PO);
    };
    virtual void 更新资金帐户PO(const 资金帐户PO& _资金帐户PO) override{
        for(资金帐户PO& 资金帐户PO_:资金帐户集合_){
            if(资金帐户PO_.账号 == _资金帐户PO.账号){
                资金帐户PO_.金额_=_资金帐户PO.金额_;
                资金帐户PO_.禁止转入_=_资金帐户PO.禁止转入_;
                资金帐户PO_.禁止转出_=_资金帐户PO.禁止转出_;
            }
        }
    } ;
    virtual boost::optional<资金帐户PO>  获取资金帐户PO(const std::string 账号) override{
        for(资金帐户PO& 资金帐户PO_:资金帐户集合_){
            if(资金帐户PO_.账号 == 账号){
               return 资金帐户PO_;
            }
        }
        return boost::none;
    }
};
#endif //TRANSFER_资金帐户DAO_H
