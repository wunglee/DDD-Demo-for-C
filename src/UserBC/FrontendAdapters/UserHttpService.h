//
// Created by 王立 on 2021/5/24.
//

#ifndef DDD_DEMO_FOR_C_用户服务端_H
#define DDD_DEMO_FOR_C_用户服务端_H
#include "../Application/UserService.h"
#include "../UserServiceFactory.h"
#include "../../../src/FrameworkComponents/LocalRequestionFilters/Response.h"
#include "../../../src/FrameworkComponents/LocalRequestionFilters/Require.h"
#include "../../../src/FrameworkComponents/LocalRequestionFilters/RequireAccepter.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "UserDTO.h"
#include "../../FrameworkComponents/NetworkProtocol/Http.h"

/**
 * 这是类其实可以是框架通过用户服务接口的服务描述自动生成的
 * 接收的参数是HTTP请求对象和响应对象，此处只是模拟，内部没有真实实现HTTP协议相关处理
 * TODO:请求对象应该在其它线程异步处理，并异步回调当前上下文后返回客户端
 */
class UserHttpService{
private:
    RequireAccepter * 请求接收器_= nullptr;
    static UserHttpService *用户HTTP服务端_;
    UserHttpService(RequireAccepter *请求接收器_): 请求接收器_(请求接收器_) {}
public:
    ~UserHttpService(){
        用户HTTP服务端_= nullptr;
    }
    static UserHttpService *构建单例(RequireAccepter * 请求接收器_) {
        if (UserHttpService::用户HTTP服务端_ == nullptr) {
            UserHttpService::用户HTTP服务端_ = new UserHttpService(请求接收器_);
        }
        return UserHttpService::用户HTTP服务端_;
    }
    static UserHttpService *获取单例() {
        if(UserHttpService::用户HTTP服务端_ == nullptr){
            throw "实例未创建";
        }
        return UserHttpService::用户HTTP服务端_;
    }
    static void 销毁单例(){
        if(UserHttpService::用户HTTP服务端_ != nullptr)
            delete UserHttpService::用户HTTP服务端_;
    }
    HttpResponse 获取用户(HttpRequest &请求)  {
        boost::optional<User> 用户_;
        /**
         * TODO:异步回调这个回调函数,并采用NOI返回给客户端
         */
        std::function<void(Response&)> 回调函数=[&](Response& 处理结果_) mutable{
            if(处理结果_.异常_==nullptr){
                用户_=boost::any_cast<User>(处理结果_.返回值);
            }
        };
        Require 获取用户请求_= Require("1",
                                 "UserRequireMapping",
                                 "获取用户",
                                 UserDTO(boost::any_cast<std::string>(请求.body)),
                                 &回调函数);
        请求接收器_->提交请求(获取用户请求_);
        HttpResponse httpResponse(用户_.value());
        return httpResponse;
    }

    HttpResponse 是否已冻结(HttpRequest &请求){
        bool 是否冻结;
        /**
        * TODO:异步回调这个回调函数
        */
        std::function<void(Response&)> 回调函数=[&](Response& 处理结果_) mutable{
            if(处理结果_.异常_==nullptr){
                是否冻结=boost::any_cast<bool>(处理结果_.返回值);
            }
        };
        Require 是否已冻结请求_= Require("1",
                                  "UserRequireMapping",
                                  "是否已冻结",
                                  UserDTO(boost::any_cast<std::string>(请求.body)),
                                  &回调函数);
        请求接收器_->提交请求(是否已冻结请求_);
        HttpResponse httpResponse(是否冻结);
        return httpResponse;
    }

    HttpResponse 添加用户(HttpRequest &请求) {
        Require 创建用户请求_= Require("1",
                                 "UserRequireMapping",
                                 "创建用户",
                                 UserDTO(boost::any_cast<std::string>(请求.body)),
                                 nullptr);
        请求接收器_->提交请求(创建用户请求_);
        return HttpResponse();
    }

    HttpResponse 冻结用户(HttpRequest &请求) {
        Require 冻结用户请求_= Require("1",
                                 "UserRequireMapping",
                                 "冻结用户",
                                 UserDTO(boost::any_cast<std::string>(请求.body)),
                                 nullptr);
        请求接收器_->提交请求(冻结用户请求_);
        return HttpResponse();
    }

    HttpResponse 解冻用户(HttpRequest &请求) {
        Require 解冻用户请求_= Require("1",
                                 "UserRequireMapping",
                                 "解冻用户",
                                 UserDTO(boost::any_cast<std::string>(请求.body)),
                                 nullptr);
        请求接收器_->提交请求(解冻用户请求_);
        return HttpResponse();
    }
};


#endif //DDD_DEMO_FOR_C_用户服务端_H
