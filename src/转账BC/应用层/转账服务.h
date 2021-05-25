#ifndef ARGS_转账服务_H
#define ARGS_转账服务_H
#include <string>
#include <boost/optional.hpp>
#include <boost/format.hpp>
#include "../领域层/转账.h"
#include "../../用户BC/应用层/用户服务.h"
#include "../../框架组件/异常.h"
#include "../../框架组件/事件发布订阅/领域事件.h"
#include "../../框架组件/事件发布订阅/事件发布订阅服务.h"
#include "../../框架组件/命名服务/命名服务管理器.h"
#include "转账仓储接口.h"
#include "转账查询接口.h"
#include "../../全局配置/服务接口/转账服务接口.h"
#include "../主适配器/转账DTO.h"
#include "../从适配器/用户HTTP客户端.h"
/**
 * TODO::所有领域事件和仓储操作必须在一个强一致事务内
 */
class 转账服务: public 转账服务接口{
private:
    用户服务接口 * 用户服务接口_;
    static 转账服务* 转账服务_;
    转账仓储接口* 转账仓储接口_;
    转账查询接口* 转账查询服务接口_;
    转账服务(转账仓储接口 *转账仓储接口, 转账查询接口 * 转账查询服务接口,用户服务接口 * 用户服务接口):
            转账仓储接口_(转账仓储接口),转账查询服务接口_(转账查询服务接口),用户服务接口_(用户服务接口){
    }
    void 完成退款(int 单号, 转账 &转账_) const {
        转账_.完成退款();
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        事件发布订阅服务::构建单例()->发布(领域事件("转账已退回", 单号,
                                  转账已到账DTO(单号, 转账_.获取付款方账号(),
                                           转账_.获取收款方账号(), 转账_.获取金额())));
    }

    void 转账到账(int 单号, 转账 &转账_) const {
        转账_.付款到账();
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        事件发布订阅服务::构建单例()->发布(领域事件("转账已到账", 单号,
                                  转账已到账DTO(单号, 转账_.获取付款方账号(),
                                           转账_.获取收款方账号(), 转账_.获取金额())));
    }

public:
    ~转账服务() {
        转账服务::转账服务_= nullptr;
    }
    static 转账服务* 构建单例(
            转账仓储接口 *转账仓储接口_,
            转账查询接口 *转账查询接口_,
            用户服务接口 * 用户服务接口_){
        if (转账服务::转账服务_ == nullptr) {
            转账服务::转账服务_ = new 转账服务(转账仓储接口_, 转账查询接口_,用户服务接口_);
        }
        return 转账服务::转账服务_;
    }
    static 转账服务* 获取单例(){
        if(转账服务::转账服务_== nullptr){
            throw "单例未创建";
        }
        return 转账服务::转账服务_;
    }
    static void 销毁单例(){
        if(转账服务::转账服务_!= nullptr)
        delete 转账服务::转账服务_;
    }
    virtual int 申请转账(std::string 付款账号, std::string 收款账号, float 金额) override{
        转账用户 付款账号_=转账用户(付款账号, 用户服务接口_->是否已冻结(付款账号));
        转账用户 收款账号_=转账用户(收款账号, 用户服务接口_->是否已冻结(收款账号));
        转账 转账_=转账::构造新的转账(付款账号_,收款账号_,金额);
        转账仓储接口_->新增转账(转账_);
        事件发布订阅服务::构建单例()->发布(领域事件("转账已创建", 转账_.获取单号(),
                                  转账已创建DTO(转账_.获取单号(), 付款账号, 金额)));
        return 转账_.获取单号();
    }
    virtual void 通知到账(int 单号,std::string 账号) override{
        转账 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        if(账号==转账_.获取收款方账号()){
            转账到账(单号, 转账_);
        }
        if(账号==转账_.获取付款方账号()){
            完成退款(单号, 转账_);
        }
    }
    virtual void 通知取消(int 单号,异常 异常) override{
        转账 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        转账_.取消(异常);
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
    }
    virtual void 通知申请退款(int 单号,异常 异常) override{
        转账 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        转账_.申请退款(异常);
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        事件发布订阅服务::构建单例()->发布(领域事件("转账退款中", 单号,
                                  转账退款事件(单号, 转账_.获取付款方账号(), 转账_.获取金额())));
    }
    virtual void 通知出账(int 单号) override{
        转账 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        转账_.付款出账();
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        事件发布订阅服务::构建单例()->发布(领域事件("转账已出账", 单号,
                                  转账已出账DTO(单号, 转账_.获取收款方账号(), 转账_.获取金额())));
    }
    virtual boost::optional<转账> 获取转账(int 单号) override {
        return 转账查询服务接口_->获取转账(单号);
    }
};
#endif //ARGS_转账服务_H
