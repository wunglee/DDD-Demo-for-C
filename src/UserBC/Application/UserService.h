#ifndef TRANSFER_用户服务_H
#define TRANSFER_用户服务_H
#include "../Domain/User.h"
#include "../../FundBC/Application/FundService.h"
#include "../../FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/UserServiceInterface.h"
#include "UserRepositoryInterface.h"
#include "UserQueryService.h"
/**
 * TODO::所有领域事件和仓储操作必须在一个强一致事务内
 */
class UserService : public UserServiceInterface{
private:
    UserRepositoryInterface * 用户仓储接口_;
    UserQueryService * 用户查询接口_;
    UserService(UserRepositoryInterface * 用户仓储接口, UserQueryService* 用户查询接口):
    用户仓储接口_(用户仓储接口),用户查询接口_(用户查询接口){}
    static UserService* 用户服务_;
public:
    ~UserService() {
        UserService::用户服务_= nullptr;
    }
    static UserService* 构建单例(UserRepositoryInterface* 用户仓储接口, UserQueryService* 用户查询接口){
        if (UserService::用户服务_ == nullptr) {
            UserService::用户服务_ = new UserService(用户仓储接口, 用户查询接口);
        }
        return UserService::用户服务_;
    }
    static UserService* 获取单例(){
        if (UserService::用户服务_ == nullptr) {
            throw "单例还未构建";
        }
        return UserService::用户服务_;
    }
    static void 销毁单例(){
        if(UserService::用户服务_ != nullptr)
          delete UserService::用户服务_;
    }
    virtual void 添加用户(std::string 账号) override{
        用户仓储接口_->添加用户(账号);
        PublishSubscribeService::构建单例()->发布(DomainEvent("用户已创建", 0, 用户已创建DTO(账号)));
    }
    virtual void 冻结用户(std::string 账号)  override{
        User 用户_ = 用户仓储接口_->获取必须存在的用户(账号);
        用户_.冻结();
        用户仓储接口_->更新用户(用户_);
    }
    virtual void 解冻用户(std::string 账号) override{
        User 用户_ =  用户仓储接口_->获取必须存在的用户(账号);
        用户_.解冻();
        用户仓储接口_->更新用户(用户_);
    }
    virtual bool 是否已冻结(std::string 账号) override{
        User 用户_ =  用户仓储接口_->获取必须存在的用户(账号);
        return 用户_.是否冻结();
    }
    virtual boost::optional<User> 获取用户(std::string 账号)override {
        return 用户查询接口_->获取用户(账号);
    }
};
#endif //TRANSFER_用户服务_H
