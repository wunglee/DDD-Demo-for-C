#ifndef TRANSFER_请求处理器管理器_H
#define TRANSFER_请求处理器管理器_H
#include <map>
#include "RequireMapping.h"
#include "RequiresQueuePoolInterface.h"
#include "../NamingService/NamingServiceManager.h"
#include "Filter.h"
#include "FiltersManager.h"
#include "RequiresQueuePool.h"
#include "Response.h"
#include "../Exception.h"
/**
 * TODO:请求处理器线程和请求发送方线程处于同一微服务，它完成微服务自身的横切业务的拦截处理，
 * 拦截后有可能需要转发到其它微服务进一步处理。
 * TODO:请求队列池的处理应该由一个线程池来完成，线程池的大小要根据CPU数量动态决定
 */
class RequireMappingsManager{
private:
    RequiresQueuePoolInterface* 请求队列池_= RequiresQueuePool::获取单例();
    std::map<std::string,RequireMapping*> 请求处理器注册表;
    RequireMappingsManager(const std::list<Filter*> 拦截器链表=std::list<Filter*>()) {
        拦截器管理器_=new 拦截器管理器(拦截器链表);
    }
    static RequireMappingsManager * 请求处理器管理器_;
    拦截器管理器 *拦截器管理器_;
public:
    ~RequireMappingsManager(){
        请求处理器注册表.clear();
        delete 拦截器管理器_;
        RequireMappingsManager::请求处理器管理器_= nullptr;
    }
    static RequireMappingsManager* 构建单例(const std::list<Filter*> 拦截器链表=std::list<Filter*>()){
        if(RequireMappingsManager::请求处理器管理器_ == nullptr){
            RequireMappingsManager::请求处理器管理器_=new RequireMappingsManager(拦截器链表);
        }
        return RequireMappingsManager::请求处理器管理器_;
    }
    static RequireMappingsManager* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(RequireMappingsManager::请求处理器管理器_ != nullptr)
            delete RequireMappingsManager::请求处理器管理器_;
    }
    void 处理(){
        boost::optional<Require> 请求_Optional;
        while ((请求_Optional= 请求队列池_->取出请求()).has_value()){
            Require 请求_=请求_Optional.value();
            RequireMapping* 请求处理器_=请求处理器注册表[请求_.获取请求处理器名称()];
            Response 处理结果_= 拦截器管理器_->拦截处理(*请求处理器_,
                                          请求_.获取方法名(),
                                          请求_.获取参数(),
                                          请求_.获取拦截器配置());
            if(请求_.获取回调方法()!= nullptr){
                请求_.获取回调方法()->operator()(处理结果_);
            }
        }
    }
    void 注册请求处理器(std::string 名称, RequireMapping *请求处理器){
        请求处理器注册表[名称]=请求处理器;
    }
    void 注销请求处理器(std::string 名称){
        请求处理器注册表.erase(名称);
    }
};


#endif //TRANSFER_请求处理器管理器_H
