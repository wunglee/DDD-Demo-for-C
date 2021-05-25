//
// Created by 王立 on 2021/5/24.
//

#ifndef DDD_DEMO_FOR_C_用户服务端_H
#define DDD_DEMO_FOR_C_用户服务端_H
#include "../应用层/用户服务.h"
#include "../用户服务工厂.h"
#include "../../../src/框架组件/请求拦截/处理结果.h"
#include "../../../src/框架组件/请求拦截/请求.h"
#include "../../../src/框架组件/请求拦截/请求接收器.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "用户DTO.h"
/**
 * 这是类其实可以是框架通过用户服务接口的服务描述自动生成的
 * 接收的参数是HTTP请求对象和响应对象，此处只是模拟，内部没有真实实现HTTP协议相关处理
 * TODO:请求对象应该在其它线程异步处理，并异步回调当前上下文后返回客户端
 */
class 用户HTTP服务端{
private:
    请求接收器 * 请求接收器_= nullptr;
    static 用户HTTP服务端 *用户HTTP服务端_;
    用户HTTP服务端(请求接收器 *请求接收器_): 请求接收器_(请求接收器_) {}
public:
    ~用户HTTP服务端(){
        用户HTTP服务端_= nullptr;
    }
    static 用户HTTP服务端 *构建单例(请求接收器 * 请求接收器_) {
        if (用户HTTP服务端::用户HTTP服务端_ == nullptr) {
            用户HTTP服务端::用户HTTP服务端_ = new 用户HTTP服务端(请求接收器_);
        }
        return 用户HTTP服务端::用户HTTP服务端_;
    }
    static 用户HTTP服务端 *获取单例() {
        if(用户HTTP服务端::用户HTTP服务端_== nullptr){
            throw "实例未创建";
        }
        return 用户HTTP服务端::用户HTTP服务端_;
    }
    static void 销毁单例(){
        if(用户HTTP服务端::用户HTTP服务端_!= nullptr)
            delete 用户HTTP服务端::用户HTTP服务端_;
    }
    boost::optional<用户> 获取用户(std::string 账号)  {
        boost::optional<用户> 用户_;
        /**
         * TODO:异步回调这个回调函数,并采用NOI返回给客户端
         */
        std::function<void(处理结果&)> 回调函数=[&](处理结果& 处理结果_) mutable{
            if(处理结果_.异常_==nullptr){
                用户_=boost::any_cast<用户>(处理结果_.返回值);
            }
        };
        请求 获取用户请求_= 请求("1",
                       "用户请求处理器",
                       "获取用户",
                       用户DTO(账号),
                       &回调函数);
        请求接收器_->提交请求(获取用户请求_);
        return 用户_;
    }

    bool 是否已冻结(std::string 账号){
        bool 是否冻结;
        /**
        * TODO:异步回调这个回调函数
        */
        std::function<void(处理结果&)> 回调函数=[&](处理结果& 处理结果_) mutable{
            if(处理结果_.异常_==nullptr){
                是否冻结=boost::any_cast<bool>(处理结果_.返回值);
            }
        };
        请求 是否已冻结请求_= 请求("1",
                       "用户请求处理器",
                       "是否已冻结",
                       用户DTO(账号),
                       &回调函数);
        请求接收器_->提交请求(是否已冻结请求_);
        return 是否冻结;
    }

    void 添加用户(std::string 账号) {
        请求 创建用户请求_= 请求("1",
                       "用户请求处理器",
                       "创建用户",
                       用户DTO(账号),
                       nullptr);
        请求接收器_->提交请求(创建用户请求_);
    }

    void 冻结用户(std::string 账号) {
        请求 冻结用户请求_= 请求("1",
                       "用户请求处理器",
                       "冻结用户",
                       用户DTO(账号),
                       nullptr);
        请求接收器_->提交请求(冻结用户请求_);
    }

    void 解冻用户(std::string 账号) {
        请求 解冻用户请求_= 请求("1",
                       "用户请求处理器",
                       "解冻用户",
                       用户DTO(账号),
                       nullptr);
        请求接收器_->提交请求(解冻用户请求_);
    }
};


#endif //DDD_DEMO_FOR_C_用户服务端_H
