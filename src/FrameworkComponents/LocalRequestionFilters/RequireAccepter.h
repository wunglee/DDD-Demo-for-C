#ifndef TRANSFER_请求接收器_H
#define TRANSFER_请求接收器_H
#include "Require.h"
#include "RequireMappingsManager.h"
#include "RequiresQueuePool.h"
#include "../NamingService/NamingServiceManager.h"

class RequireAccepter{
private:
    RequiresQueuePoolInterface* 请求队列池_= RequiresQueuePool::获取单例();
    RequireMappingsManager* 请求处理器管理器_= RequireMappingsManager::获取单例();
    RequireAccepter(){
    }
    void 幂等处理(std::string 请求ID){
    }
    static RequireAccepter* 请求接收器_;
public:
    ~RequireAccepter() {
        RequireAccepter::请求接收器_= nullptr;
    }
    static RequireAccepter* 构建单例(){
        if(RequireAccepter::请求接收器_ == nullptr){
            RequireAccepter::请求接收器_=new RequireAccepter();
        }
        return RequireAccepter::请求接收器_;
    }
    static RequireAccepter* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(RequireAccepter::请求接收器_ != nullptr)
           delete RequireAccepter::请求接收器_;
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



#endif //TRANSFER_请求接收器_H
