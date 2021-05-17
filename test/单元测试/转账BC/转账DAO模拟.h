#ifndef TRANSFER_转账DAO模拟_H
#define TRANSFER_转账DAO模拟_H
#include "../../../src/转账BC/从适配器/转账PO.h"
#include "../../../src/转账BC/从适配器/转账DAO接口.h"
class 转账DAO模拟: public 转账DAO接口{
private:
    std::vector<转账PO> 转账集合_;
    static 转账DAO模拟* 转账DAO模拟_;
    转账DAO模拟() {}
public:
    ~转账DAO模拟() {
        转账DAO模拟::转账DAO模拟_= nullptr;
        转账集合_.clear();
    }
    static 转账DAO模拟* 获取单例(){
        if (转账DAO模拟_ == nullptr) {
            转账DAO模拟_ = new 转账DAO模拟();
        }
        return 转账DAO模拟_;
    }
    virtual void 新增转账PO(const 转账PO &转账PO) override{
        转账集合_.push_back(转账PO);
    }
    virtual boost::optional<转账PO> 获取转账PO(int 单号) override{
        for(转账PO 转账PO_: 转账集合_){
           if(转账PO_.单号==单号){
               return 转账PO_;
           }
        }
        return boost::none;
    };
    virtual void 更新转账PO状态(int 单号,int 状态) override{
        for(转账PO& 转账PO_: 转账集合_){
            if(转账PO_.单号==单号){
                转账PO_.状态=状态;
            }
        }
    };
};


#endif //TRANSFER_转账DAO模拟_H
