#ifndef TRANSFER_请求接收器_H
#define TRANSFER_请求接收器_H
#include "请求.h"
#include "请求处理器管理器.h"
#include "请求队列池.h"
#include "../命名服务/命名服务管理器.h"

class 请求接收器{
private:
    请求队列池接口* 请求队列池_= 请求队列池::获取单例();
    请求处理器管理器* 请求处理器管理器_= 请求处理器管理器::获取单例();
    请求接收器(){
    }
    void 幂等处理(std::string 请求ID){
    }
    static 请求接收器* 请求接收器_;
public:
    ~请求接收器() {
        请求接收器::请求接收器_= nullptr;
    }
    static 请求接收器* 构建单例(){
        if(请求接收器::请求接收器_== nullptr){
            请求接收器::请求接收器_=new 请求接收器();
        }
        return 请求接收器::请求接收器_;
    }
    static 请求接收器* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(请求接收器::请求接收器_!= nullptr)
           delete 请求接收器::请求接收器_;
    }
    void 提交请求(请求& 请求){
        幂等处理(请求.获取请求Id());
        请求队列池_->加入请求(请求);
        /**
         * TODO:此处的处理应该在另一个线程中异步完成并调用参数中的回调函数。
         */
        请求处理器管理器_->处理();
    }
};



#endif //TRANSFER_请求接收器_H
