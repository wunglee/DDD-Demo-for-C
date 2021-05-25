#ifndef TRANSFER_事件发布订阅服务_H
#define TRANSFER_事件发布订阅服务_H
#include "DomainEvent.h"
#include "EventMonitor.h"
#include "../NamingService/NamingServiceManager.h"

class PublishSubscribeService {
private:
    typedef std::map<std::string,std::vector<std::string>> 监听器注册表;
    监听器注册表 监听器注册表_;
    PublishSubscribeService(){}
    static PublishSubscribeService* 事件发布订阅服务_;
public:
    ~PublishSubscribeService() {
        PublishSubscribeService::事件发布订阅服务_= nullptr;
        监听器注册表_.clear();
    }
    static PublishSubscribeService* 构建单例(){
        if(事件发布订阅服务_== nullptr){
            事件发布订阅服务_=new PublishSubscribeService();
        }
        return 事件发布订阅服务_;
    }
    static PublishSubscribeService* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        delete PublishSubscribeService::事件发布订阅服务_;
    }
    void 订阅(std::string 事件名, std::string 监听器名称){
        监听器注册表_[事件名].push_back(监听器名称);
    }
    void 发布(DomainEvent 领域事件_){
        幂等处理(领域事件_.获取事件名(),领域事件_.获取事务ID());
        /**
         * TODO:需要发布到可靠消息中心，并在另一个线程或进程中异步处理。
         */
        for(std::string 监听器名称:监听器注册表_[领域事件_.获取事件名()]){
            boost::optional<EventMonitor*> 事件监听器_ = NamingServiceManager::获取单例()->查找服务<EventMonitor *>(监听器名称);
            if(事件监听器_.has_value()){
                事件监听器_.value()->处理(领域事件_);
            }
        }
    }
    void 幂等处理(std::string 事件名,long 请求ID){
    }
    void 清空注册表(){
        监听器注册表_.clear();
    }
};


#endif //TRANSFER_事件发布订阅服务_H
