#ifndef TRANSFER_转账事件监听器_H
#define TRANSFER_转账事件监听器_H
#include "../../FrameworkComponents/DomainEvent/EventMonitor.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/FundServiceInterface.h"
#include "../../TransferBC/FrontendAdapters/TransferDTO.h"
//从事件队列中取出事件进行处理
class FundEventMapping : public EventMonitor{
private:
    static FundEventMapping* 资金事件处理器_;
    FundServiceInterface * 资金帐户请求服务接口_= nullptr;
    FundEventMapping(FundServiceInterface * 资金帐户请求服务接口): 资金帐户请求服务接口_(资金帐户请求服务接口){}
public:
    ~FundEventMapping() {
        FundEventMapping::资金事件处理器_= nullptr;
    }
    static FundEventMapping* 构建单例(FundServiceInterface * 资金帐户请求服务接口){
        assert(资金帐户请求服务接口!= nullptr);
        if (FundEventMapping::资金事件处理器_ == nullptr) {
            FundEventMapping::资金事件处理器_ = new FundEventMapping(资金帐户请求服务接口);
        }
        return FundEventMapping::资金事件处理器_;
    }
    static FundEventMapping* 获取单例(){
        if(FundEventMapping::资金事件处理器_ == nullptr){
            throw "单例未创建";
        }
        return FundEventMapping::资金事件处理器_;
    }
    static void 销毁单例(){
        if(FundEventMapping::资金事件处理器_ != nullptr){
            delete FundEventMapping::资金事件处理器_;
        }
    }
    //TODO:还需要重构，并且不应该直接调用应用服务，应该转发给请求拦截器进一步处理
    std::map<std::string,std::function<void(DomainEvent)>> 事件处理映射表;
    void 处理(const DomainEvent 领域事件_){
        boost::any 事件内容;
        std::string 事件名 = 领域事件_.获取事件名();
        if(事件名=="转账已创建"){
                事件内容=领域事件_.获取内容();
                转账已创建DTO 转账已创建事件内容_=boost::any_cast<转账已创建DTO>(事件内容);
                资金帐户请求服务接口_->扣减资金(转账已创建事件内容_.转账单号,转账已创建事件内容_.付款方账号,转账已创建事件内容_.付款金额);
        }
        if(事件名=="用户已创建") {
            事件内容 = 领域事件_.获取内容();
            用户已创建DTO 用户已创建事件内容_ = boost::any_cast<用户已创建DTO>(事件内容);
            资金帐户请求服务接口_->添加资金帐户(用户已创建事件内容_.用户名);
        }
        if(事件名=="转账已出账") {
            事件内容 = 领域事件_.获取内容();
            转账已出账DTO 转账已出账事件内容_ = boost::any_cast<转账已出账DTO>(事件内容);
            资金帐户请求服务接口_->增加资金(转账已出账事件内容_.转账单号, 转账已出账事件内容_.收款方账号, 转账已出账事件内容_.金额);
        }
        if(事件名=="转账退款中") {
            事件内容 = 领域事件_.获取内容();
            转账退款事件 转账退款事件内容_ = boost::any_cast<转账退款事件>(事件内容);
            资金帐户请求服务接口_->增加资金(转账退款事件内容_.单号, 转账退款事件内容_.退回账号, 转账退款事件内容_.金额);
        }
    };
};
#endif //TRANSFER_转账事件监听器_H
