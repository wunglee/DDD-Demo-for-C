#ifndef TRANSFER_UserRepository_H
#define TRANSFER_UserRepository_H
#include "boost/optional.hpp"

#include "../application/user_repository_interface.h"
#include "../domain/user.h"
#include "user_dao_interface.h"
#include "user_po.h"

#ifndef BOOST_OPTIONAL_CONFIG_USE_OLD_IMPLEMENTATION_OF_OPTIONAL

class UserRepository : public UserRepositoryInterface {
 private:
  UserDAOInterface* userDAOInterface_;
  UserRepository(UserDAOInterface* userDAOInterface) : userDAOInterface_(userDAOInterface) {}
  static UserRepository* userRepository_;

 public:
  ~UserRepository() { UserRepository::userRepository_ = nullptr; }

  static UserRepository* BuildInstance(UserDAOInterface* userDAOInterface_) {
    if (UserRepository::userRepository_ == nullptr) {
      UserRepository::userRepository_ = new UserRepository(userDAOInterface_);
    }
    return UserRepository::userRepository_;
  }
  static UserRepository* GetInstance() {
    if (UserRepository::userRepository_ == nullptr) {
      throw "单例未创建";
    }
    return UserRepository::userRepository_;
  }
  static void DestroyInstance() {
    if (UserRepository::userRepository_ != nullptr) delete UserRepository::userRepository_;
  }
  virtual void AddUser(std::string account_id) override {
    userDAOInterface_->AddUserPO(UserPO(account_id));
  };
  virtual void UpdateUser(User& user_) override {
    userDAOInterface_->UpdateUserPO(UserPO(user_.GetAccountId(), user_.isFrozen()));
  };
  User GetExistedUser(std::string account_id) override {
    boost::optional<UserPO> userPO_optianal = userDAOInterface_->GetUserPO(account_id);
    if (userPO_optianal.has_value()) {
      return User(userPO_optianal.value().account_id_, userPO_optianal.value().frozen_);
    }
    throw Exception((boost::format("没有找到用户:%1%") % account_id).str());
  }
};

#endif

#endif  // TRANSFER_UserRepository_H
