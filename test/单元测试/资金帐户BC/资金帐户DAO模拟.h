#ifndef TRANSFER_资金帐户DAO模拟_H
#define TRANSFER_资金帐户DAO模拟_H
#include "../../../src/资金帐户BC/从适配器/资金帐户DAO接口.h"
#include "../../../src/资金帐户BC/从适配器/资金帐户PO.h"

class 资金帐户DAO模拟 : public 资金帐户DAO接口 {
    std::vector<资金帐户PO> 资金帐户集合_;
    static 资金帐户DAO模拟* 资金帐户DAO模拟_;
    资金帐户DAO模拟(){}
public:
    ~资金帐户DAO模拟() {
        资金帐户DAO模拟::资金帐户DAO模拟_= nullptr;
        资金帐户集合_.clear();
    }
    static 资金帐户DAO模拟* 构建单例(){
        if (资金帐户DAO模拟_ == nullptr) {
            资金帐户DAO模拟_ = new 资金帐户DAO模拟();
        }
        return 资金帐户DAO模拟_;
    }
    static 资金帐户DAO模拟* 获取已存在的单例(){
        return 资金帐户DAO模拟_;
    }
    virtual void 新增资金帐户PO(const 资金帐户PO& 资金帐户PO)override {
        资金帐户集合_.push_back(资金帐户PO);
    };
    virtual void 更新资金帐户PO(const 资金帐户PO& _资金帐户PO)override{
        for(资金帐户PO& 资金帐户PO_:资金帐户集合_){
            if(资金帐户PO_.账号 == _资金帐户PO.账号){
                资金帐户PO_.金额_=_资金帐户PO.金额_;
                资金帐户PO_.禁止转入_=_资金帐户PO.禁止转入_;
                资金帐户PO_.禁止转出_=_资金帐户PO.禁止转出_;
            }
        }
    };
    virtual boost::optional<资金帐户PO>  获取资金帐户PO(const std::string 账号)override{
        for(资金帐户PO& 资金帐户PO_:资金帐户集合_){
            if(资金帐户PO_.账号 ==账号){
                return 资金帐户PO_;
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_资金帐户DAO模拟_H
