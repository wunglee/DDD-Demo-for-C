#ifndef TRANSFER_用户服务_H
#define TRANSFER_用户服务_H
#include "../领域层/用户.h"
#include "../../资金帐户BC/应用层/资金帐户服务.h"
#include "../../框架组件/命名服务/命名服务管理器.h"
#include "../../全局配置/服务接口/用户服务接口.h"
#include "用户仓储接口.h"
#include "用户查询接口.h"
class 用户服务 : public 用户服务接口{
private:
    用户仓储接口 * 用户仓储接口_;
    用户查询接口 * 用户查询接口_;
    用户服务(用户仓储接口 * 用户仓储接口,用户查询接口* 用户查询接口):
    用户仓储接口_(用户仓储接口),用户查询接口_(用户查询接口){}
    static 用户服务* 用户服务_;
public:
    ~用户服务() {
        用户服务::用户服务_= nullptr;
    }
    static 用户服务* 构建单例(用户仓储接口* 用户仓储接口, 用户查询接口* 用户查询接口){
        if (用户服务::用户服务_ == nullptr) {
            用户服务::用户服务_ = new 用户服务(用户仓储接口,用户查询接口);
        }
        return 用户服务::用户服务_;
    }
    static 用户服务* 获取单例(){
        if (用户服务::用户服务_ == nullptr) {
            throw "单例还未构建";
        }
        return 用户服务::用户服务_;
    }
    static void 销毁单例(){
        if(用户服务::用户服务_!= nullptr)
          delete 用户服务::用户服务_;
    }
    virtual void 添加用户(std::string 账号) override{
        用户仓储接口_->添加用户(账号);
        事件发布订阅服务::构建单例()->发布(领域事件("用户已创建", 0, 用户已创建DTO(账号)));
    }
    virtual void 冻结用户(std::string 账号)  override{
        用户 用户_ = 用户仓储接口_->获取必须存在的用户(账号);
        用户_.冻结();
        用户仓储接口_->更新用户(用户_);
    }
    virtual void 解冻用户(std::string 账号) override{
        用户 用户_ =  用户仓储接口_->获取必须存在的用户(账号);
        用户_.解冻();
        用户仓储接口_->更新用户(用户_);
    }
    virtual bool 是否已冻结(std::string 账号) override{
        用户 用户_ =  用户仓储接口_->获取必须存在的用户(账号);
        return 用户_.是否冻结();
    }
    virtual boost::optional<用户> 获取用户(std::string 账号)override {
        return 用户查询接口_->获取用户(账号);
    }
};
#endif //TRANSFER_用户服务_H
