#ifndef TRANSFER_转账前端控制器_H
#define TRANSFER_转账前端控制器_H
#include "../../../src/FrameworkComponents/RequestionFilters/RequireMapping.h"
#include "../../../src/FrameworkComponents/RequestionFilters/Response.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../../src/GlobalBusinessDependency/ServiceInterfaces/UserServiceInterface.h"
#include "boost/any.hpp"
#include "UserDTO.h"
class UserRequireMapping : public RequireMapping{
private:
    UserServiceInterface * 用户服务接口_;
    static UserRequireMapping* 用户请求处理器_;
    UserRequireMapping(UserServiceInterface *用户服务接口_) : 用户服务接口_(用户服务接口_) {}
public:
    virtual ~UserRequireMapping(){
        UserRequireMapping::用户请求处理器_= nullptr;
    }
    static UserRequireMapping* 构建单例(UserServiceInterface * 用户服务接口){
        if (UserRequireMapping::用户请求处理器_ == nullptr) {
            UserRequireMapping::用户请求处理器_ = new UserRequireMapping(用户服务接口);
        }
        return UserRequireMapping::用户请求处理器_;
    }
    static UserRequireMapping* 获取单例(){
        if (UserRequireMapping::用户请求处理器_ == nullptr) {
            throw "单例未构建";
        }
        return UserRequireMapping::用户请求处理器_;
    }
    static void 销毁单例(){
        if(UserRequireMapping::用户请求处理器_ != nullptr){
            delete UserRequireMapping::用户请求处理器_;
        }
    }
    virtual Response 处理(std::string 方法名, const boost::any &方法参数) override {
        Response 处理结果_;
        if(方法名=="创建用户") {
            UserDTO 用户DTO_=boost::any_cast<UserDTO>(方法参数);
            用户服务接口_->添加用户(用户DTO_.用户名);
        }
        if(方法名=="冻结用户") {
            UserDTO 用户DTO_=boost::any_cast<UserDTO>(方法参数);
            用户服务接口_->冻结用户(用户DTO_.用户名);
        }
        if(方法名=="解冻用户") {
            UserDTO 用户DTO_=boost::any_cast<UserDTO>(方法参数);
            用户服务接口_->解冻用户(用户DTO_.用户名);
        }
        if(方法名=="获取用户") {
            UserDTO 用户DTO_=boost::any_cast<UserDTO>(方法参数);
            boost::optional<User>  用户_ = 用户服务接口_->获取用户(用户DTO_.用户名);
            if(用户_.has_value()){
                处理结果_.返回值=用户_.value();
            }else{
                处理结果_.异常_=std::make_shared<Exception>("未查到该用户");
            }
        }
        if(方法名=="是否已冻结") {
            UserDTO 用户DTO_=boost::any_cast<UserDTO>(方法参数);
            bool 冻结_ = 用户服务接口_->是否已冻结(用户DTO_.用户名);
            处理结果_.返回值=冻结_;
        }
        return 处理结果_;
    }
};


#endif //TRANSFER_转账前端控制器_H
