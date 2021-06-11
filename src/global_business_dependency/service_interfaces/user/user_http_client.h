#ifndef DDD_DEMO_FOR_C_USER_HTTP_CLIENT_H
#define DDD_DEMO_FOR_C_USER_HTTP_CLIENT_H
#include "../../../bc/user/frontend_adapters/user_http_service.h"
#include "../../../framework_components/naming_service/naming_service_manager.h"
/**
 * 这是类其实可以是框架通过服务描述自动生成的
 * 此处只是模拟，内部没有真实实现HTTP协议相关处理
 */
class  UserHttpClient: public UserServiceInterface{
private:
    UserHttpService* userHttpService_= NamingServiceManager::GetInstance()->Find_Service<UserHttpService *>("用户HTTP服务").value();
    static UserHttpClient *user_http_client_;
    UserHttpClient() {}
public:
    ~UserHttpClient(){
        user_http_client_= nullptr;
    }
    static UserHttpClient *BuildInstance() {
        if (UserHttpClient::user_http_client_ == nullptr) {
            UserHttpClient::user_http_client_ = new UserHttpClient();
        }
        return UserHttpClient::user_http_client_;
    }
    static UserHttpClient *GetInstance() {
        return BuildInstance();
    }
    static void DestroyInstance(){
        if(UserHttpClient::user_http_client_ != nullptr)
            delete UserHttpClient::user_http_client_;
    }
/**
 * 真实项目是获取服务地址并对请求参数进行序列化操作
 */
    boost::optional<UserDTO> GetUser(std::string account_id){
        HttpRequest httpRequest("",account_id);
        boost::any body = userHttpService_->GetUser(httpRequest).body;
        if(!body.empty()){
            return  boost::any_cast<UserDTO>(body);
        }
        return  boost::none;

    }

    bool IsFrozen(std::string account_id){
        HttpRequest httpRequest("",account_id);
        HttpResponse httpResponse= userHttpService_->IsFrozen(httpRequest);
        return boost::any_cast<bool>(httpResponse.body);
    }

    void AddUser(std::string account_id) {
        HttpRequest httpRequest("",account_id);
        userHttpService_->AddUser(httpRequest);
    }

    void FreezeUser(std::string account_id) {
        HttpRequest httpRequest("",account_id);
        userHttpService_->FreezeUser(httpRequest);
    }

    void UnfreezeUser(std::string account_id) {
        HttpRequest httpRequest("",account_id);
        userHttpService_->UnfreezeUser(httpRequest);
    }
};
#endif //DDD_DEMO_FOR_C_USER_HTTP_CLIENT_H
