//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_转账查询模拟_H
#define TRANSFER_转账查询模拟_H
#include "../../../src/TransferBC/Application/TransferQueryInterface.h"
class TransferQueryMock: public TransferQueryInterface {
    std::vector<Transfer> &转账集合_;
    static TransferQueryMock* 转账查询模拟_;
    TransferQueryMock(std::vector<Transfer> &转账集合): 转账集合_(转账集合){
    }
public:
    ~TransferQueryMock() {
        TransferQueryMock::转账查询模拟_= nullptr;
    }
    static TransferQueryMock* 获取单例(std::vector<Transfer> &转账集合_){
        if (转账查询模拟_ == nullptr) {
            转账查询模拟_ = new TransferQueryMock(转账集合_);
        }
        return 转账查询模拟_;
    }
    static TransferQueryMock* 获取已存在的单例(){
        return 转账查询模拟_;
    }
    boost::optional<Transfer> 获取转账(int 单号) override {
        for(Transfer& 转账_:转账集合_){
            if(转账_.获取单号()==单号){
                return 转账_;
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_转账查询模拟_H
