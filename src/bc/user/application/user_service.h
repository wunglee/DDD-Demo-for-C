#ifndef TRANSFER_UserService_H
#define TRANSFER_UserService_H
#include "boost/optional.hpp"

#include "../../../framework_components/naming_service/naming_service_manager.h"
#include "../../../global_business_dependency/service_interfaces/user/user_service_interface.h"
#include "../../fund/application/fund_service.h"
#include "../domain/user.h"
#include "user_query_service.h"
#include "user_repository_interface.h"
/**
 * TODO::所有领域事件和仓储操作必须在一个强一致事务内
 */
class UserService : public UserServiceInterface {
 private:
  UserRepositoryInterface* userRepositoryInterface_;
  UserQueryService* userQueryService_;
  UserService(UserRepositoryInterface* userRepositoryInterface, UserQueryService* userQueryService)
      : userRepositoryInterface_(userRepositoryInterface), userQueryService_(userQueryService) {}
  static UserService* userService_;

 public:
  ~UserService() { UserService::userService_ = nullptr; }
  static UserService* BuildInstance(
      UserRepositoryInterface* userRepositoryInterface, UserQueryService* userQueryService) {
    assert(userRepositoryInterface != nullptr);
    assert(userQueryService != nullptr);

    if (UserService::userService_ == nullptr) {
      UserService::userService_ = new UserService(userRepositoryInterface, userQueryService);
    }
    return UserService::userService_;
  }
  static UserService* GetInstance() {
    if (UserService::userService_ == nullptr) {
      throw "单例还未构建";
    }
    return UserService::userService_;
  }
  static void DestroyInstance() {
    if (UserService::userService_ != nullptr) delete UserService::userService_;
  }
  virtual void AddUser(std::string account_id) override {
    userRepositoryInterface_->AddUser(account_id);
    PublishSubscribeService::BuildInstance()->Publish(
        DomainEvent("用户已创建", rand(), UserCreatedDTO(account_id).Serialize()));
  }
  virtual void FreezeUser(std::string account_id) override {
    User user_ = userRepositoryInterface_->GetExistedUser(account_id);
    user_.freeze();
    userRepositoryInterface_->UpdateUser(user_);
  }
  virtual void UnfreezeUser(std::string account_id) override {
    User user_ = userRepositoryInterface_->GetExistedUser(account_id);
    user_.unfreeze();
    userRepositoryInterface_->UpdateUser(user_);
  }
  virtual bool IsFrozen(std::string account_id) override {
    User user_ = userRepositoryInterface_->GetExistedUser(account_id);
    return user_.isFrozen();
  }
  virtual boost::optional<UserDTO> GetUser(std::string account_id) override {
    boost::optional<User> user_optional = userQueryService_->GetUser(account_id);
    if (user_optional.has_value()) {
      User user = user_optional.value();
      return UserDTO(user.GetAccountId(), user.isFrozen());
    }
    return boost::none;
  }
};
#endif  // TRANSFER_UserService_H
