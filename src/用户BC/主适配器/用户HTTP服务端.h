//
// Created by 王立 on 2021/5/24.
//

#ifndef DDD_DEMO_FOR_C_用户服务端_H
#define DDD_DEMO_FOR_C_用户服务端_H
#include "../应用层/用户服务.h"
#include "../用户服务工厂.h"
/**
 * 这是类其实可以是框架通过用户服务接口的服务描述自动生成的
 * 此处只是模拟，内部没有真实实现HTTP协议相关处理
 */
class 用户HTTP服务端{
private:
    用户服务接口 * 用户服务接口_=用户服务工厂::获取单例();
    static 用户HTTP服务端 *用户HTTP服务端_;
    用户HTTP服务端() {}
public:
    ~用户HTTP服务端(){
        用户服务工厂::销毁单例();
        用户HTTP服务端_= nullptr;
    }
    static 用户HTTP服务端 *构建单例() {
        if (用户HTTP服务端::用户HTTP服务端_ == nullptr) {
            用户HTTP服务端::用户HTTP服务端_ = new 用户HTTP服务端();
        }
        return 用户HTTP服务端::用户HTTP服务端_;
    }
    static 用户HTTP服务端 *获取单例() {
        return 构建单例();
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
    }

    void 解冻用户(std::string 账号) {
        用户服务接口_->解冻用户(账号);
    }
};


#endif //DDD_DEMO_FOR_C_用户服务端_H
