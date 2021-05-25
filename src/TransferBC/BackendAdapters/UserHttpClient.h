#ifndef DDD_DEMO_FOR_C_USERHTTPCLIENT_H
#define DDD_DEMO_FOR_C_USERHTTPCLIENT_H
#include "../../UserBC/FrontendAdapters/UserHttpService.h"
#include "../../FrameworkComponents/NamingService/NamingServiceManager.h"
/**
 * 这是类其实可以是框架通过服务描述自动生成的
 * 此处只是模拟，内部没有真实实现HTTP协议相关处理
 */
class  UserHttpClient: public UserServiceInterface{
private:
    UserHttpService* 用户HTTP服务端_= NamingServiceManager::获取单例()->查找服务<UserHttpService*>("用户HTTP服务").value();
    static UserHttpClient *用户HTTP客户端_;
    UserHttpClient() {}
public:
    ~UserHttpClient(){
        用户HTTP客户端_= nullptr;
    }
    static UserHttpClient *构建单例() {
        if (UserHttpClient::用户HTTP客户端_ == nullptr) {
            UserHttpClient::用户HTTP客户端_ = new UserHttpClient();
        }
        return UserHttpClient::用户HTTP客户端_;
    }
    static UserHttpClient *获取单例() {
        return 构建单例();
    }
    static void 销毁单例(){
        if(UserHttpClient::用户HTTP客户端_ != nullptr)
            delete UserHttpClient::用户HTTP客户端_;
    }
/**
 * 真实项目是获取服务地址并对请求参数进行序列化操作
 */
    boost::optional<User> 获取用户(std::string 账号){
        HttpRequest httpRequest("",账号);
        return boost::any_cast<User>(用户HTTP服务端_->获取用户(httpRequest));
    }

    bool 是否已冻结(std::string 账号){
        HttpRequest httpRequest("",账号);
        HttpResponse httpResponse=用户HTTP服务端_->是否已冻结(httpRequest);
        return boost::any_cast<bool>(httpResponse.body);
    }

    void 添加用户(std::string 账号) {
        HttpRequest httpRequest("",账号);
        用户HTTP服务端_->添加用户(httpRequest);
    }

    void 冻结用户(std::string 账号) {
        HttpRequest httpRequest("",账号);
        用户HTTP服务端_->冻结用户(httpRequest);
    }

    void 解冻用户(std::string 账号) {
        HttpRequest httpRequest("",账号);
        用户HTTP服务端_->解冻用户(httpRequest);
    }
};
#endif //DDD_DEMO_FOR_C_USERHTTPCLIENT_H
