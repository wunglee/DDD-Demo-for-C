#ifndef TRANSFER_用户查询服务_H
#define TRANSFER_用户查询服务_H
#include "../应用层/用户查询接口.h"

class 用户查询: public 用户查询接口{
private:
    用户DAO接口* 用户DAO接口_;
    用户查询(用户DAO接口 * 用户DAO接口):用户DAO接口_(用户DAO接口){}
    static 用户查询 *用户查询_;
public:
    ~用户查询() {
        用户查询::用户查询_ = nullptr;
    }
    static 用户查询 *构建单例(用户DAO接口* 用户DAO接口_) {
        if (用户查询::用户查询_ == nullptr) {
            用户查询::用户查询_ = new 用户查询(用户DAO接口_);
        }
        return 用户查询::用户查询_;
    }
    static 用户查询 *获取单例() {
        if(用户查询::用户查询_== nullptr){
            throw "单例未创建";
        }
        return 用户查询::用户查询_;
    }
    static void 销毁单例(){
        if(用户查询::用户查询_!= nullptr)
          delete 用户查询::用户查询_;
    }
    virtual boost::optional<用户> 获取用户(std::string 账号) override{
        boost::optional<用户PO> 用户PO_= 用户DAO接口_->获取用户PO(账号);
        if(用户PO_.has_value()){
            return 用户(用户PO_.value().账号_, 用户PO_.value().是否冻结_);
        }
        return boost::none;
    }
};


#endif //TRANSFER_用户查询服务_H
