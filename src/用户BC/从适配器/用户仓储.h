#ifndef TRANSFER_用户仓储_H
#define TRANSFER_用户仓储_H
#include "../应用层/用户仓储接口.h"
#include "用户PO.h"
#include "../领域层/用户.h"
#include "用户DAO接口.h"

class 用户仓储 : public 用户仓储接口 {
private:
    用户DAO接口* 用户DAO接口_;
    用户仓储(用户DAO接口 * 用户DAO接口):用户DAO接口_(用户DAO接口){}
    static 用户仓储 *用户仓储_;
public:
    ~用户仓储() {
        用户仓储::用户仓储_ = nullptr;
    }

    static 用户仓储 *构建单例(用户DAO接口* 用户DAO接口_) {
        if (用户仓储::用户仓储_ == nullptr) {
            用户仓储::用户仓储_ = new 用户仓储(用户DAO接口_);
        }
        return 用户仓储::用户仓储_;
    }
    static 用户仓储 *获取单例() {
        if(用户仓储::用户仓储_== nullptr){
            throw "单例未创建";
        }
        return 用户仓储::用户仓储_;
    }
    static void 销毁单例() {
        if(用户仓储::用户仓储_!= nullptr)
           delete 用户仓储::用户仓储_;
    }
    virtual void 添加用户(std::string 账号) override{
        用户DAO接口_->添加用户PO(用户PO(账号));
    };
    virtual void 更新用户(用户 &用户_) override{
        用户DAO接口_->更新用户PO(用户PO(用户_.获取账号(),用户_.是否冻结()));
    };
    virtual 用户 获取必须存在的用户(std::string 账号) override{
        boost::optional<用户PO> 用户PO_= 用户DAO接口_->获取用户PO(账号);
        if(用户PO_.has_value()){
            return 用户(用户PO_.value().账号_, 用户PO_.value().是否冻结_);
        }
        throw 异常((boost::format("没有找到用户:%1%")%账号).str());
    }
};
#endif //TRANSFER_用户仓储_H
