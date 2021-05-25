#ifndef TRANSFER_资金帐户服务_H
#define TRANSFER_资金帐户服务_H

#include "../../FrameworkComponents/DomainEvent/PublishSubscribeService.h"
#include "../../FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/FundServiceInterface.h"
#include "FundRepositoryInterface.h"
#include "FundServiceQueryInterface.h"
#include "../FrontendAdapters/FundDTO.h"
/**
 * TODO::所有领域事件和仓储操作必须在一个强一致事务内
 */
class FundService : public FundServiceInterface{
private:
    FundRepositoryInterface * 资金帐户仓储接口_;
    FundServiceQueryInterface * 资金帐户查询服务接口_;
    FundService(FundRepositoryInterface * 资金帐户仓储接口, FundServiceQueryInterface* 资金帐户查询服务接口)
    : 资金帐户仓储接口_(资金帐户仓储接口),资金帐户查询服务接口_(资金帐户查询服务接口){}
    static FundService* 资金帐户服务_;
public:
    virtual ~FundService() {
        FundService::资金帐户服务_= nullptr;
    }
    static FundService* 构建单例(FundRepositoryInterface * 资金帐户仓储接口, FundServiceQueryInterface * 资金帐户查询服务接口_){
        assert(资金帐户仓储接口!= nullptr&&资金帐户查询服务接口_!= nullptr);
        if (FundService::资金帐户服务_ == nullptr) {
            FundService::资金帐户服务_ = new FundService(资金帐户仓储接口, 资金帐户查询服务接口_);
        }
        return FundService::资金帐户服务_;
    }
    static void 销毁单例(){
        if(FundService::资金帐户服务_ != nullptr)
           delete FundService::资金帐户服务_;
    }
    static FundService* 获取单例(){
        if(FundService::资金帐户服务_ == nullptr){
            throw "单例未创建";
        }
        return FundService::资金帐户服务_;
    }
    virtual void 初始化资金(std::string 账号, float 金额) override{
        Fund 资金帐户_ = 资金帐户仓储接口_->获取必须存在的资金帐户(账号);
        资金帐户_.增加金额(金额);
        资金帐户仓储接口_->更新资金帐户(资金帐户_);
    }
    virtual void 增加资金(int 单号,std::string 账号,float 金额) override{
        Fund 资金帐户_ = 资金帐户仓储接口_->获取必须存在的资金帐户(账号);
        if(资金帐户_.是否禁止转入()){
            PublishSubscribeService::构建单例()->发布(DomainEvent("增资已失败", 单号,
                                                            Exception((boost::format("收款方禁止收款:%s") % 账号).str())));
            return;
        }
        资金帐户_.增加金额(金额);
        资金帐户仓储接口_->更新资金帐户(资金帐户_);
        PublishSubscribeService::构建单例()->发布(DomainEvent("增资已成功", 单号, 增资已成功DTO(单号, 账号, 金额)));
    }
    virtual void 扣减资金(int 单号, std::string 账号, float 金额) override{
        Fund 资金帐户_=资金帐户仓储接口_->获取必须存在的资金帐户(账号);
        if(资金帐户_.是否禁止转出()){
            PublishSubscribeService::构建单例()->发布(DomainEvent("扣减已失败", 单号,
                                                            Exception((boost::format("付款方禁止转账:%s") % 账号).str())));
            return;
        }
        if(!资金帐户_.是否足额(金额)){
            PublishSubscribeService::构建单例()->发布(DomainEvent("扣减已失败", 单号,
                                                            Exception((boost::format("付款方金额不足，少于%f元") % 金额).str())));
            return;
        }
        资金帐户_.扣减金额(金额);
        资金帐户仓储接口_->更新资金帐户(资金帐户_);
        PublishSubscribeService::构建单例()->发布(DomainEvent("扣减已成功", 单号, 单号));
    }
    virtual void  设置禁止收款(std::string 账号, bool 是否禁止) override{
        Fund 资金帐户_=资金帐户仓储接口_->获取必须存在的资金帐户(账号);
        资金帐户_.设置禁止转入(是否禁止);
        资金帐户仓储接口_->更新资金帐户(资金帐户_);
    }
    virtual void  设置禁止付款(std::string 账号, bool 是否禁止) override{
        Fund 资金帐户_=资金帐户仓储接口_->获取必须存在的资金帐户(账号);
        资金帐户_.设置禁止转出(是否禁止);
        资金帐户仓储接口_->更新资金帐户(资金帐户_);
    }
    virtual void 添加资金帐户(std::string 账号) override{
        Fund 资金帐户(账号);
        资金帐户仓储接口_->新增资金帐户(资金帐户);
    }
    virtual boost::optional<Fund> 获取资金帐户(std::string 账号) override{
        return 资金帐户查询服务接口_->获取资金帐户(账号);
    }
};
#endif //TRANSFER_资金帐户服务_H
