#ifndef TRANSFER_资金帐户查询模拟_H
#define TRANSFER_资金帐户查询模拟_H
#include "../../../src/资金帐户BC/应用层/资金帐户查询接口.h"
class 资金帐户查询模拟 : public 资金帐户查询接口 {
private:
    std::vector<资金帐户> &资金帐户集合_;
    static 资金帐户查询模拟* 资金帐户查询模拟_;
    资金帐户查询模拟(std::vector<资金帐户> &资金帐户集合):资金帐户集合_(资金帐户集合) {}
public:
    ~资金帐户查询模拟() {
        资金帐户查询模拟::资金帐户查询模拟_= nullptr;
        资金帐户集合_.clear();
    }
    static 资金帐户查询模拟* 构建单例(std::vector<资金帐户> &资金帐户集合){
        if (资金帐户查询模拟_ == nullptr) {
            资金帐户查询模拟_ = new 资金帐户查询模拟(资金帐户集合);
        }
        return 资金帐户查询模拟_;
    }
    static 资金帐户查询模拟* 获取已存在的单例(){
        return 资金帐户查询模拟_;
    }
    virtual boost::optional<资金帐户> 获取资金帐户(std::string 账号) override{
            for(资金帐户& 资金帐户_:资金帐户集合_){
                if(资金帐户_.获取账号()==账号){
                    return 资金帐户(资金帐户_.获取账号(),
                                资金帐户_.是否禁止转出(),
                                资金帐户_.是否禁止转入(),
                                资金帐户_.获取金额());
                }
            }
        return boost::none;
    }
};

#endif //TRANSFER_资金帐户查询模拟_H
