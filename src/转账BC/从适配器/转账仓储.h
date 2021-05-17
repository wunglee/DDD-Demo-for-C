#ifndef TRANSFER_转账仓储_H
#define TRANSFER_转账仓储_H
#include "../应用层/转账仓储接口.h"
#include "转账PO.h"
#include "转账DAO接口.h"

class 转账仓储 : public 转账仓储接口{
private:
    用户服务接口 *用户服务_;
    转账DAO接口 * 转账DAO接口_;
    static 转账仓储* 转账仓储_;
    转账仓储(用户服务接口 *用户服务_,转账DAO接口* 转账DAO接口):用户服务_(用户服务_),转账DAO接口_(转账DAO接口) {}
public:
    ~转账仓储() {
        转账仓储::转账仓储_= nullptr;
    }
    static 转账仓储* 构建单例(用户服务接口 *用户服务_, 转账DAO接口 * 转账DAO接口_){
        if (转账仓储::转账仓储_ == nullptr) {
            转账仓储::转账仓储_ = new 转账仓储(用户服务_,转账DAO接口_);
        }
        return 转账仓储::转账仓储_;
    }
    static 转账仓储* 获取单例(){
        if(转账仓储::转账仓储_== nullptr){
            throw "单例未创建";
        }
        return 转账仓储::转账仓储_;
    }
    static void 销毁单例(){
        if(转账仓储::转账仓储_!= nullptr)
          delete 转账仓储::转账仓储_;
    }
    virtual void 新增转账(const 转账& 转账_) override{
        转账PO 转账PO(转账_.获取单号(),
                  转账_.获取付款方账号(),
                  转账_.获取收款方账号(),
                  转账_.获取状态(),
                  转账_.获取金额());
        转账DAO接口_->新增转账PO(转账PO);
    }
    virtual 转账 获取必须存在的转账(int 单号) override{
        boost::optional<转账PO> 转账PO_=转账DAO接口_->获取转账PO(单号);
        if(转账PO_.has_value()){
            if(转账PO_.value().单号 == 单号){
                return 转账::构造旧的转账(转账PO_.value().单号,
                          转账用户(转账PO_.value().付款方账号,
                          用户服务_->是否已冻结(转账PO_.value().付款方账号)),
                                  转账用户(转账PO_.value().收款方账号,
                          用户服务_->是否已冻结(转账PO_.value().收款方账号)),
                           转账PO_.value().金额,
                           转账::状态(转账PO_.value().状态));
            }
        }
        throw 异常((boost::format("没有找到转账单:%1%")%单号).str());;
    }
    virtual void 更新转账状态(int 单号,转账::状态 状态) override{
        转账DAO接口_->更新转账PO状态(单号,状态);
    }
};


#endif //TRANSFER_转账仓储_H
