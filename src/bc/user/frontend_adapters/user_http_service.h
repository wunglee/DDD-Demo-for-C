#ifndef DDD_DEMO_FOR_C_UserHttpService_H
#define DDD_DEMO_FOR_C_UserHttpService_H
#include "../application/user_service.h"
#include "../../../../test/integration_test/user_service_factory_for_integration.h"
#include "../../../framework_components/requestion_filters/response.h"
#include "../../../framework_components/requestion_filters/require.h"
#include "../../../framework_components/requestion_filters/require_interceptor.h"
#include "../../../framework_components/naming_service/naming_service_manager.h"
#include "../../../global_business_dependency/service_interfaces/user/user_dto.h"
#include "../../../framework_components/network_protocol/http.h"

class UserHttpService{
private:
    RequireInterceptor * require_interceptor_= nullptr;
    static UserHttpService *userHttpService_;
    UserHttpService(RequireInterceptor *require_interceptor_):
    require_interceptor_(require_interceptor_) {}
public:
    ~UserHttpService(){
        userHttpService_= nullptr;
    }
    static UserHttpService *BuildInstance(RequireInterceptor * require_interceptor_) {
        if (UserHttpService::userHttpService_ == nullptr) {
            UserHttpService::userHttpService_ = new UserHttpService(require_interceptor_);
        }
        return UserHttpService::userHttpService_;
    }
    static UserHttpService *GetInstance() {
        if(UserHttpService::userHttpService_ == nullptr){
            throw "实例未创建";
        }
        return UserHttpService::userHttpService_;
    }
    static void DestroyInstance(){
        if(UserHttpService::userHttpService_ != nullptr)
            delete UserHttpService::userHttpService_;
    }
    HttpResponse GetUser(HttpRequest &httpRequest)  {
        Require require= Require("1",
                                 "UserRequireMapping",
                                 "GetUser",
                                 UserDTO(boost::any_cast<std::string>(httpRequest.body)));
        Response response=require_interceptor_->Commit(require);
        boost::optional<UserDTO> user_optional=boost::any_cast<boost::optional<UserDTO>>(response.value);
        if(user_optional.has_value()){
            return  HttpResponse(user_optional.value());
        };
        return HttpResponse();
    }

    HttpResponse IsFrozen(HttpRequest &httpRequest){
        Require require= Require("1",
                                 "UserRequireMapping",
                                 "IsFrozen",
                                 UserDTO(boost::any_cast<std::string>(httpRequest.body)));
        Response response=require_interceptor_->Commit(require);
        HttpResponse httpResponse(boost::any_cast<bool>(response.value));
        return httpResponse;
    }

    HttpResponse AddUser(HttpRequest &httpRequest) {
        Require require= Require("1",
                                 "UserRequireMapping",
                                 "create_user",
                                 UserDTO(boost::any_cast<std::string>(httpRequest.body)));
        require_interceptor_->Commit(require);
        return HttpResponse();
    }

    HttpResponse FreezeUser(HttpRequest &httpRequest) {
        Require require= Require("1",
                                 "UserRequireMapping",
                                 "FreezeUser",
                                 UserDTO(boost::any_cast<std::string>(httpRequest.body)));
        require_interceptor_->Commit(require);
        return HttpResponse();
    }

    HttpResponse UnfreezeUser(HttpRequest &httpRequest) {
        Require require= Require("1",
                                 "UserRequireMapping",
                                 "UnfreezeUser",
                                 UserDTO(boost::any_cast<std::string>(httpRequest.body)));
        require_interceptor_->Commit(require);
        return HttpResponse();
    }
};


#endif //DDD_DEMO_FOR_C_UserHttpService_H
