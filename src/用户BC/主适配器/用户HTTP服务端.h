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
/**
 * 这是类其实可以是框架通过用户服务接口的服务描述自动生成的
 * 此处只是模拟，内部没有真实实现HTTP协议相关处理
 */
class 用户HTTP服务端{
private:
    用户服务接口 * 用户服务接口_;
    请求接收器 * 请求接收器_= nullptr;
    static 用户HTTP服务端 *用户HTTP服务端_;
//    请求 构造请求(std::string 请求参数,std::function<void(处理结果&)>& 回调函数){
//        申请转账DTO 申请转账DTO_("XX","YY",10);
//        请求 请求_("1",
//               "转账请求处理器",
//               "申请转账",
//               申请转账DTO_,
//               回调函数);
//        return 请求_;
//    }
    用户HTTP服务端(请求接收器 *请求接收器_,用户服务接口 * 用户服务接口_)
            : 请求接收器_(请求接收器_),用户服务接口_(用户服务接口_) {}
    用户HTTP服务端(用户服务接口 * 用户服务接口_)
            : 用户服务接口_(用户服务接口_) {}
public:
    ~用户HTTP服务端(){
        用户服务工厂::销毁单例();
        用户HTTP服务端_= nullptr;
    }
    static 用户HTTP服务端 *构建单例(用户服务接口 *用户服务接口_) {
        if (用户HTTP服务端::用户HTTP服务端_ == nullptr) {
            用户HTTP服务端::用户HTTP服务端_ = new 用户HTTP服务端(用户服务接口_);
        }
        return 用户HTTP服务端::用户HTTP服务端_;
    }
    static 用户HTTP服务端 *构建单例(请求接收器 * 请求接收器_,用户服务接口 *用户服务接口_) {
        if (用户HTTP服务端::用户HTTP服务端_ == nullptr) {
            用户HTTP服务端::用户HTTP服务端_ = new 用户HTTP服务端(请求接收器_,用户服务接口_);
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
        return 用户服务接口_->获取用户(账号);
    }

    bool 是否已冻结(std::string 账号){
        return 用户服务接口_->是否已冻结(账号);
    }

    void 添加用户(std::string 账号) {
        用户服务接口_->添加用户(账号);
    }

    void 冻结用户(std::string 账号) {
        用户服务接口_->冻结用户(账号);
//        int 单号;
//        std::function<void(处理结果&)> 回调函数=[&](处理结果& 处理结果_) mutable{
//            if(处理结果_.异常_==nullptr){
//                单号=boost::any_cast<int>(处理结果_.返回值);
//            }
//        };
//        请求 请求_=构造请求(账号,回调函数);
//        请求接收器_->提交请求(请求_);
    }

    void 解冻用户(std::string 账号) {
        用户服务接口_->解冻用户(账号);
    }
};


#endif //DDD_DEMO_FOR_C_用户服务端_H
