#ifndef DDD_DEMO_FOR_C_用户HTTP客户端_H
#define DDD_DEMO_FOR_C_用户HTTP客户端_H
#include "../../用户BC/主适配器/用户HTTP服务端.h"
#include "../../框架组件/命名服务/命名服务管理器.h"
/**
 * 这是类其实可以是框架通过服务描述自动生成的
 * 此处只是模拟，内部没有真实实现HTTP协议相关处理
 */
class  用户HTTP客户端: public 用户服务接口{
private:
    用户HTTP服务端* 用户HTTP服务端_= 命名服务管理器::获取单例()->查找服务<用户HTTP服务端*>("用户HTTP服务").value();
    static 用户HTTP客户端 *用户HTTP客户端_;
    用户HTTP客户端() {}
public:
    ~用户HTTP客户端(){
        用户HTTP客户端_= nullptr;
    }
    static 用户HTTP客户端 *构建单例() {
        if (用户HTTP客户端::用户HTTP客户端_ == nullptr) {
            用户HTTP客户端::用户HTTP客户端_ = new 用户HTTP客户端();
        }
        return 用户HTTP客户端::用户HTTP客户端_;
    }
    static 用户HTTP客户端 *获取单例() {
        return 构建单例();
    }
    static void 销毁单例(){
        if(用户HTTP客户端::用户HTTP客户端_!= nullptr)
            delete 用户HTTP客户端::用户HTTP客户端_;
    }
/**
 * 真实项目是获取服务地址并请求参数的序列化操作
 */
    boost::optional<用户> 获取用户(std::string 账号){
        return 用户HTTP服务端_->获取用户(账号);
    }

    bool 是否已冻结(std::string 账号){
        return 用户HTTP服务端_->是否已冻结(账号);
    }

    void 添加用户(std::string 账号) {
        用户HTTP服务端_->添加用户(账号);
    }

    void 冻结用户(std::string 账号) {
        用户HTTP服务端_->冻结用户(账号);
    }

    void 解冻用户(std::string 账号) {
        用户HTTP服务端_->解冻用户(账号);
    }
};
#endif //DDD_DEMO_FOR_C_用户HTTP客户端_H
