//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_转账仓储模拟_H
#define TRANSFER_转账仓储模拟_H
#include "../../../src/全局配置/服务接口/用户服务接口.h"
#include "../../../src/转账BC/应用层/转账仓储接口.h"
#include "../../../src/转账BC/领域层/转账.h"
#include "../../../src/转账BC/领域层/转账用户.h"

class 转账仓储模拟 : public 转账仓储接口{
private:
    std::vector<转账> &转账集合_;
    用户服务接口* 用户服务接口_;
    static 转账仓储模拟 * 转账仓储模拟_;
    转账仓储模拟(std::vector<转账> &转账集合,用户服务接口* 用户服务接口):
    转账集合_(转账集合),用户服务接口_(用户服务接口){
    }
public:
    ~转账仓储模拟() {
        转账仓储模拟::转账仓储模拟_= nullptr;
    }
    static 转账仓储模拟* 获取单例(std::vector<转账> &转账集合_,用户服务接口* 用户服务接口_){
        if (转账仓储模拟_ == nullptr) {
            转账仓储模拟_ = new 转账仓储模拟(转账集合_,用户服务接口_);
        }
        return 转账仓储模拟_;
    }
    static 转账仓储模拟* 获取已存在的单例(){
        return 转账仓储模拟_;
    }
    void 新增转账(const 转账& 转账_) override {
        转账集合_.push_back(转账_);
    }

    转账 获取必须存在的转账(int 单号) override {
        for(转账 &转账_:转账集合_){
            if(转账_.获取单号()==单号){
                return 转账::构造旧的转账(转账_.获取单号(),
                        转账用户(转账_.获取付款方账号(),
                        用户服务接口_->是否已冻结(转账_.获取付款方账号())),
                        转账用户(转账_.获取收款方账号(),
                       用户服务接口_->是否已冻结(转账_.获取收款方账号())),
                        转账_.获取金额(),转账_.获取状态());
            }
        }
        throw new 异常("没有找到");
    }

    void 更新转账状态(int 单号, 转账::状态 状态) override {
        for(转账 & 转账_:转账集合_){
            if(转账_.获取单号()==单号){
                return 转账_.更新状态(状态);
            }
        }
    }
};


#endif //TRANSFER_转账仓储模拟_H
