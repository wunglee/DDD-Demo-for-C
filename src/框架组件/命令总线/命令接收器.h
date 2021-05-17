#ifndef TRANSFER_命令接收器_H
#define TRANSFER_命令接收器_H
#include "命令.h"
#include "命令处理器管理器.h"
#include "命令队列池.h"
#include "../命名服务/命名服务管理器.h"

class 命令接收器{
private:
    命令队列池接口* 命令队列池_= 命名服务管理器::获取单例()->查找服务<命令队列池接口 *>("命令队列池").value();
    命令处理器管理器* 命令处理器管理器_= 命名服务管理器::获取单例()->查找服务<命令处理器管理器 *>("命令处理器管理器").value();
    命令接收器(){
    }
    void 幂等处理(std::string 命令ID){
    }
    static 命令接收器* 命令接收器_;
public:
    ~命令接收器() {
        命令接收器::命令接收器_= nullptr;
    }
    static 命令接收器* 构建单例(){
        if(命令接收器::命令接收器_== nullptr){
            命令接收器::命令接收器_=new 命令接收器();
        }
        return 命令接收器::命令接收器_;
    }
    static 命令接收器* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(命令接收器::命令接收器_!= nullptr)
           delete 命令接收器::命令接收器_;
    }
    void 提交命令(命令& 命令){
        幂等处理(命令.获取命令Id());
        命令队列池_->加入命令(命令);
        命令处理器管理器_->处理();
    }
};



#endif //TRANSFER_命令接收器_H
