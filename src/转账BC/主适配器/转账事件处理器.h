#ifndef TRANSFER_转账事件处理器_H
#define TRANSFER_转账事件处理器_H
#include "../../框架组件/事件总线/事件监听器.h"
#include "../应用层/转账服务接口.h"
#include "../../资金帐户BC/主适配器/资金事件DTO.h"
//从事件队列中取出事件进行处理
class 转账事件处理器 : public 事件监听器{
private:
    static 转账事件处理器* 转账事件处理器_;
    转账服务接口 * 转账服务接口_;
    转账事件处理器(转账服务接口 * 转账服务接口): 转账服务接口_(转账服务接口){
    }
public:
    virtual ~转账事件处理器() {
        转账事件处理器::转账事件处理器_= nullptr;
    }
    static 转账事件处理器* 构建单例(转账服务接口 * 转账服务接口_){
        if (转账事件处理器::转账事件处理器_ == nullptr) {
            转账事件处理器::转账事件处理器_ = new 转账事件处理器(转账服务接口_);
        }
        return 转账事件处理器::转账事件处理器_;
    }
    static 转账事件处理器* 获取单例(){
        if (转账事件处理器::转账事件处理器_ == nullptr) {
            throw "单例未构建";
        }
        return 转账事件处理器::转账事件处理器_;
    }
    static void 销毁单例(){
        if(转账事件处理器::转账事件处理器_!= nullptr){
            delete 转账事件处理器::转账事件处理器_;
        }
    }
    virtual void 处理(领域事件 领域事件_) override{
        std::string 事件名= 领域事件_.获取事件名();
        if(事件名=="扣减已成功") {
            int 转账单号 = 领域事件_.获取事务ID();
            转账服务接口_->通知出账(转账单号);
        }
        if(事件名=="扣减已失败") {
                int 转账单号 = 领域事件_.获取事务ID();
                boost::any 事件内容=领域事件_.获取内容();
                异常 异常_=boost::any_cast<异常>(事件内容);
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
            异常 异常_ = boost::any_cast<异常>(事件内容);
            转账服务接口_->通知申请退款(转账单号, 异常_);
        }
    };
};


#endif //TRANSFER_转账事件处理器_H
