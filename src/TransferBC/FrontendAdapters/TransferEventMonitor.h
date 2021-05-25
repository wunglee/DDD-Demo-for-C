#ifndef TRANSFER_转账事件处理器_H
#define TRANSFER_转账事件处理器_H
#include "../../FrameworkComponents/DomainEvent/EventMonitor.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/TransferServiceInterface.h"
#include "../../FundBC/FrontendAdapters/FundDTO.h"
//从事件队列中取出事件进行处理
class TransferEventMonitor : public EventMonitor{
private:
    static TransferEventMonitor* 转账事件处理器_;
    TransferServiceInterface * 转账服务接口_;
    TransferEventMonitor(TransferServiceInterface * 转账服务接口): 转账服务接口_(转账服务接口){
    }
public:
    virtual ~TransferEventMonitor() {
        TransferEventMonitor::转账事件处理器_= nullptr;
    }
    static TransferEventMonitor* 构建单例(TransferServiceInterface * 转账服务接口_){
        if (TransferEventMonitor::转账事件处理器_ == nullptr) {
            TransferEventMonitor::转账事件处理器_ = new TransferEventMonitor(转账服务接口_);
        }
        return TransferEventMonitor::转账事件处理器_;
    }
    static TransferEventMonitor* 获取单例(){
        if (TransferEventMonitor::转账事件处理器_ == nullptr) {
            throw "单例未构建";
        }
        return TransferEventMonitor::转账事件处理器_;
    }
    static void 销毁单例(){
        if(TransferEventMonitor::转账事件处理器_ != nullptr){
            delete TransferEventMonitor::转账事件处理器_;
        }
    }
    //TODO:还需要重构，并且不应该直接调用应用服务，应该转发给请求过滤器进一步处理
    virtual void 处理(DomainEvent 领域事件_) override{
        std::string 事件名= 领域事件_.获取事件名();
        if(事件名=="扣减已成功") {
            int 转账单号 = 领域事件_.获取事务ID();
            转账服务接口_->通知出账(转账单号);
        }
        if(事件名=="扣减已失败") {
                int 转账单号 = 领域事件_.获取事务ID();
                boost::any 事件内容=领域事件_.获取内容();
                Exception 异常_=boost::any_cast<Exception>(事件内容);
                转账服务接口_->通知取消(转账单号, 异常_);
         }
        if(事件名=="增资已成功") {
            boost::any 事件内容 = 领域事件_.获取内容();
            增资已成功DTO 增资已成功事件内容_ = boost::any_cast<增资已成功DTO>(事件内容);
            转账服务接口_->通知到账(增资已成功事件内容_.单号, 增资已成功事件内容_.增资账号);
        }
        if(事件名=="增资已失败") {
            int 转账单号 = 领域事件_.获取事务ID();
            boost::any 事件内容 = 领域事件_.获取内容();
            Exception 异常_ = boost::any_cast<Exception>(事件内容);
            转账服务接口_->通知申请退款(转账单号, 异常_);
        }
    };
};


#endif //TRANSFER_转账事件处理器_H
