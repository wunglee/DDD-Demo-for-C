#ifndef ARGS_转账服务_H
#define ARGS_转账服务_H
#include <string>
#include <boost/optional.hpp>
#include <boost/format.hpp>
#include "../Domain/Transfer.h"
#include "../../FrameworkComponents/Exception.h"
#include "../../FrameworkComponents/DomainEvent/DomainEvent.h"
#include "../../FrameworkComponents/DomainEvent/PublishSubscribeService.h"
#include "TransferRepositoryInterface.h"
#include "TransferQueryInterface.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/TransferServiceInterface.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/UserServiceInterface.h"
#include "../FrontendAdapters/TransferDTO.h"
/**
 * TODO::所有领域事件和仓储操作必须在一个强一致事务内
 */
class TransferService: public TransferServiceInterface{
private:
    UserServiceInterface * 用户服务接口_;
    static TransferService* 转账服务_;
    TransferRepositoryInterface* 转账仓储接口_;
    TransferQueryInterface* 转账查询服务接口_;
    TransferService(TransferRepositoryInterface *转账仓储接口, TransferQueryInterface * 转账查询服务接口, UserServiceInterface * 用户服务接口):
            转账仓储接口_(转账仓储接口),转账查询服务接口_(转账查询服务接口),用户服务接口_(用户服务接口){
    }
    void 完成退款(int 单号, Transfer &转账_) const {
        转账_.完成退款();
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        PublishSubscribeService::构建单例()->发布(DomainEvent("转账已退回", 单号,
                                                        转账已到账DTO(单号, 转账_.获取付款方账号(),
                                           转账_.获取收款方账号(), 转账_.获取金额())));
    }

    void 转账到账(int 单号, Transfer &转账_) const {
        转账_.付款到账();
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        PublishSubscribeService::构建单例()->发布(DomainEvent("转账已到账", 单号,
                                                        转账已到账DTO(单号, 转账_.获取付款方账号(),
                                           转账_.获取收款方账号(), 转账_.获取金额())));
    }

public:
    ~TransferService() {
        TransferService::转账服务_= nullptr;
    }
    static TransferService* 构建单例(
            TransferRepositoryInterface *转账仓储接口_,
            TransferQueryInterface *转账查询接口_,
            UserServiceInterface * 用户服务接口_){
        if (TransferService::转账服务_ == nullptr) {
            TransferService::转账服务_ = new TransferService(转账仓储接口_, 转账查询接口_, 用户服务接口_);
        }
        return TransferService::转账服务_;
    }
    static TransferService* 获取单例(){
        if(TransferService::转账服务_ == nullptr){
            throw "单例未创建";
        }
        return TransferService::转账服务_;
    }
    static void 销毁单例(){
        if(TransferService::转账服务_ != nullptr)
        delete TransferService::转账服务_;
    }
    virtual int 申请转账(std::string 付款账号, std::string 收款账号, float 金额) override{
        TransferUser 付款账号_=TransferUser(付款账号, 用户服务接口_->是否已冻结(付款账号));
        TransferUser 收款账号_=TransferUser(收款账号, 用户服务接口_->是否已冻结(收款账号));
        Transfer 转账_=Transfer::构造新的转账(付款账号_, 收款账号_, 金额);
        转账仓储接口_->新增转账(转账_);
        PublishSubscribeService::构建单例()->发布(DomainEvent("转账已创建", 转账_.获取单号(),
                                                        转账已创建DTO(转账_.获取单号(), 付款账号, 金额)));
        return 转账_.获取单号();
    }
    virtual void 通知到账(int 单号,std::string 账号) override{
        Transfer 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        if(账号==转账_.获取收款方账号()){
            转账到账(单号, 转账_);
        }
        if(账号==转账_.获取付款方账号()){
            完成退款(单号, 转账_);
        }
    }
    virtual void 通知取消(int 单号, Exception 异常) override{
        Transfer 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        转账_.取消(异常);
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
    }
    virtual void 通知申请退款(int 单号, Exception 异常) override{
        Transfer 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        转账_.申请退款(异常);
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        PublishSubscribeService::构建单例()->发布(DomainEvent("转账退款中", 单号,
                                                        转账退款事件(单号, 转账_.获取付款方账号(), 转账_.获取金额())));
    }
    virtual void 通知出账(int 单号) override{
        Transfer 转账_= 转账仓储接口_->获取必须存在的转账(单号);
        转账_.付款出账();
        转账仓储接口_->更新转账状态(转账_.获取单号(),转账_.获取状态());
        PublishSubscribeService::构建单例()->发布(DomainEvent("转账已出账", 单号,
                                                        转账已出账DTO(单号, 转账_.获取收款方账号(), 转账_.获取金额())));
    }
    virtual boost::optional<Transfer> 获取转账(int 单号) override {
        return 转账查询服务接口_->获取转账(单号);
    }
};
#endif //ARGS_转账服务_H
