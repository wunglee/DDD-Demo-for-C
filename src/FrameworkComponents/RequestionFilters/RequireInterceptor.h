#ifndef TRANSFER_请求拦截器_H
#define TRANSFER_请求拦截器_H
#include "Require.h"
#include "RequireMappingsManager.h"
#include "RequiresQueuePool.h"
#include "../NamingService/NamingServiceManager.h"

class RequireInterceptor{
private:
    RequiresQueuePoolInterface* 请求队列池_= RequiresQueuePool::获取单例();
    RequireMappingsManager* 请求处理器管理器_= RequireMappingsManager::获取单例();
    RequireInterceptor(){
    }
    void 幂等处理(std::string 请求ID){
    }
    static RequireInterceptor* 请求拦截器_;
public:
    ~RequireInterceptor() {
        RequireInterceptor::请求拦截器_= nullptr;
    }
    static RequireInterceptor* 构建单例(){
        if(RequireInterceptor::请求拦截器_ == nullptr){
            RequireInterceptor::请求拦截器_=new RequireInterceptor();
        }
        return RequireInterceptor::请求拦截器_;
    }
    static RequireInterceptor* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(RequireInterceptor::请求拦截器_ != nullptr)
           delete RequireInterceptor::请求拦截器_;
    }
    void 提交请求(Require& 请求){
        幂等处理(请求.获取请求Id());
        请求队列池_->加入请求(请求);
        /**
         * TODO:此处的处理应该在另一个线程中异步完成并调用参数中的回调函数。
         */
        请求处理器管理器_->处理();
    }
};



#endif //TRANSFER_请求拦截器_H
