#ifndef TRANSFER_查询服务_H
#define TRANSFER_查询服务_H
#include "../应用层/转账仓储接口.h"
#include "../应用层/转账查询接口.h"
#include "转账DAO接口.h"
#include "转账PO.h"
#include "../领域层/转账用户.h"
#include "用户HTTP客户端.h"
class 转账查询: public 转账查询接口{
private:
    用户服务接口 * 用户服务接口_;
    转账DAO接口 * 转账DAO接口_;
    转账查询(转账DAO接口* 转账DAO接口,用户服务接口 * 用户服务接口):转账DAO接口_(转账DAO接口),用户服务接口_(用户服务接口){}
    static 转账查询* 转账查询_;
public:
    virtual boost::optional<转账> 获取转账(int 单号) override {
        boost::optional<转账PO> 转账PO_=转账DAO接口_->获取转账PO(单号);
        if(转账PO_.has_value()){
            return 转账::构造旧的转账(转账PO_.value().单号,
                              转账用户(转账PO_.value().付款方账号,
                                   用户服务接口_->是否已冻结(转账PO_.value().付款方账号)),
                              转账用户(转账PO_.value().收款方账号,
                                   用户服务接口_->是否已冻结(转账PO_.value().收款方账号)),
                              转账PO_.value().金额,
                              转账::状态(转账PO_.value().状态));
        }
        return boost::none;
    }
    ~转账查询() {
        转账查询::转账查询_= nullptr;
    }
    static 转账查询* 构建单例(转账DAO接口* 转账DAO接口,用户服务接口 * 用户服务接口){
        if (转账查询::转账查询_ == nullptr) {
            转账查询::转账查询_ = new 转账查询(转账DAO接口,用户服务接口);
        }
        return 转账查询::转账查询_;
    }
    static 转账查询* 获取单例(){
        if(转账查询::转账查询_== nullptr){
            throw "单例未创建";
        }
        return 转账查询::转账查询_;
    }
    static void 销毁单例(){
        if(转账查询::转账查询_!= nullptr)
          delete 转账查询::转账查询_;
    }
};


#endif //TRANSFER_查询服务_H
