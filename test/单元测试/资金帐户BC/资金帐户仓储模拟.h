#ifndef TRANSFER_资金帐户仓储模拟_H
#define TRANSFER_资金帐户仓储模拟_H
#include "../../../src/资金帐户BC/应用层/资金帐户仓储接口.h"
class 资金帐户仓储模拟 : public 资金帐户仓储接口{
private:
    std::vector<资金帐户> & 资金帐户集合_;
    static 资金帐户仓储模拟* 资金帐户仓储模拟_;
    资金帐户仓储模拟(std::vector<资金帐户> &资金帐户集合):资金帐户集合_(资金帐户集合){}
public:
    ~资金帐户仓储模拟() {
        资金帐户仓储模拟::资金帐户仓储模拟_= nullptr;
    }
    static 资金帐户仓储模拟* 构建单例(std::vector<资金帐户> &资金帐户集合){
        if (资金帐户仓储模拟_ == nullptr) {
            资金帐户仓储模拟_ = new 资金帐户仓储模拟(资金帐户集合);
        }
        return 资金帐户仓储模拟_;
    }
    static 资金帐户仓储模拟* 获取已存在的单例(){
        return 资金帐户仓储模拟_;
    }
    virtual void 新增资金帐户(资金帐户& 资金帐户) override{
        资金帐户集合_.push_back(资金帐户);
    }
    virtual void 更新资金帐户(资金帐户& _资金帐户) override{
        for(资金帐户& 资金帐户_:资金帐户集合_){
            if(资金帐户_.获取账号()==_资金帐户.获取账号()){
                //不知道如何替换集合中的原有对象，只能替换原有对象的内容
                资金帐户_.设置禁止转出(_资金帐户.是否禁止转出());
                资金帐户_.设置禁止转入(_资金帐户.是否禁止转入());
                //并且不能破坏原有对象的封装，导致很丑的代码
                资金帐户_.扣减金额(资金帐户_.获取金额());
                资金帐户_.增加金额(_资金帐户.获取金额());
            }
        }
    }
};


#endif //TRANSFER_资金帐户仓储模拟_H
