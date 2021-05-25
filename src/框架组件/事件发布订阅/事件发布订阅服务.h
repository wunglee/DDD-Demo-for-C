#ifndef TRANSFER_事件发布订阅服务_H
#define TRANSFER_事件发布订阅服务_H
#include "领域事件.h"
#include "事件监听器.h"
#include "../命名服务/命名服务管理器.h"

class 事件发布订阅服务 {
private:
    typedef std::map<std::string,std::vector<std::string>> 监听器注册表;
    监听器注册表 监听器注册表_;
    事件发布订阅服务(){}
    static 事件发布订阅服务* 事件发布订阅服务_;
public:
    ~事件发布订阅服务() {
        事件发布订阅服务::事件发布订阅服务_= nullptr;
        监听器注册表_.clear();
    }
    static 事件发布订阅服务* 构建单例(){
        if(事件发布订阅服务_== nullptr){
            事件发布订阅服务_=new 事件发布订阅服务();
        }
        return 事件发布订阅服务_;
    }
    static 事件发布订阅服务* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        delete 事件发布订阅服务::事件发布订阅服务_;
    }
    void 订阅(std::string 事件名, std::string 监听器名称){
        监听器注册表_[事件名].push_back(监听器名称);
    }
    void 发布(领域事件 领域事件_){
        幂等处理(领域事件_.获取事件名(),领域事件_.获取事务ID());
        /**
         * TODO:需要发布到可靠消息中心，并在另一个线程或进程中异步处理。
         */
        for(std::string 监听器名称:监听器注册表_[领域事件_.获取事件名()]){
            boost::optional<事件监听器*> 事件监听器_ = 命名服务管理器::获取单例()->查找服务<事件监听器 *>(监听器名称);
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
