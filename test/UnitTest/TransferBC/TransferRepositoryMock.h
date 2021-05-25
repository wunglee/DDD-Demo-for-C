//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_转账仓储模拟_H
#define TRANSFER_转账仓储模拟_H
#include "../../../src/GlobalBusinessDependency/ServiceInterfaces/UserServiceInterface.h"
#include "../../../src/TransferBC/Application/TransferRepositoryInterface.h"
#include "../../../src/TransferBC/Domain/Transfer.h"
#include "../../../src/TransferBC/Domain/TransferUser.h"

class TransferRepositoryMock : public TransferRepositoryInterface{
private:
    std::vector<Transfer> &转账集合_;
    UserServiceInterface* 用户服务接口_;
    static TransferRepositoryMock * 转账仓储模拟_;
    TransferRepositoryMock(std::vector<Transfer> &转账集合, UserServiceInterface* 用户服务接口):
    转账集合_(转账集合),用户服务接口_(用户服务接口){
    }
public:
    ~TransferRepositoryMock() {
        TransferRepositoryMock::转账仓储模拟_= nullptr;
    }
    static TransferRepositoryMock* 获取单例(std::vector<Transfer> &转账集合_, UserServiceInterface* 用户服务接口_){
        if (转账仓储模拟_ == nullptr) {
            转账仓储模拟_ = new TransferRepositoryMock(转账集合_, 用户服务接口_);
        }
        return 转账仓储模拟_;
    }
    static TransferRepositoryMock* 获取已存在的单例(){
        return 转账仓储模拟_;
    }
    void 新增转账(const Transfer& 转账_) override {
        转账集合_.push_back(转账_);
    }

    Transfer 获取必须存在的转账(int 单号) override {
        for(Transfer &转账_:转账集合_){
            if(转账_.获取单号()==单号){
                return Transfer::构造旧的转账(转账_.获取单号(),
                                        TransferUser(转账_.获取付款方账号(),
                                                     用户服务接口_->是否已冻结(转账_.获取付款方账号())),
                                        TransferUser(转账_.获取收款方账号(),
                                                     用户服务接口_->是否已冻结(转账_.获取收款方账号())),
                                        转账_.获取金额(), 转账_.获取状态());
            }
        }
        throw new Exception("没有找到");
    }

    void 更新转账状态(int 单号, Transfer::状态 状态) override {
        for(Transfer & 转账_:转账集合_){
            if(转账_.获取单号()==单号){
                return 转账_.更新状态(状态);
            }
        }
    }
};


#endif //TRANSFER_转账仓储模拟_H
