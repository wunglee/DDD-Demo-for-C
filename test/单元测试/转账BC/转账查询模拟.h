//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_转账查询模拟_H
#define TRANSFER_转账查询模拟_H
#include "../../../src/转账BC/应用层/转账查询接口.h"
class 转账查询模拟: public 转账查询接口 {
    std::vector<转账> &转账集合_;
    static 转账查询模拟* 转账查询模拟_;
    转账查询模拟(std::vector<转账> &转账集合):转账集合_(转账集合){
    }
public:
    ~转账查询模拟() {
        转账查询模拟::转账查询模拟_= nullptr;
    }
    static 转账查询模拟* 获取单例(std::vector<转账> &转账集合_){
        if (转账查询模拟_ == nullptr) {
            转账查询模拟_ = new 转账查询模拟(转账集合_);
        }
        return 转账查询模拟_;
    }
    static 转账查询模拟* 获取已存在的单例(){
        return 转账查询模拟_;
    }
    boost::optional<转账> 获取转账(int 单号) override {
        for(转账& 转账_:转账集合_){
            if(转账_.获取单号()==单号){
                return 转账_;
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_转账查询模拟_H
