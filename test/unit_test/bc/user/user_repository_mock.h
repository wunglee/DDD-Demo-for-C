#ifndef TRANSFER_UserRepositoryMock_H
#define TRANSFER_UserRepositoryMock_H

#include <vector>

#include "../../../../src/bc/user/application/user_repository_interface.h"
#include "../../../../src/bc/user/domain/user.h"

class UserRepositoryMock : public UserRepositoryInterface {
 private:
  std::vector<User>& users_;
  UserRepositoryMock(std::vector<User>& users) : users_(users) {}
  static UserRepositoryMock* userRepositoryMock;

 public:
  ~UserRepositoryMock() { UserRepositoryMock::userRepositoryMock = nullptr; }

  static UserRepositoryMock* BuildInstance(std::vector<User>& users) {
    if (userRepositoryMock == nullptr) {
      userRepositoryMock = new UserRepositoryMock(users);
    }
    return userRepositoryMock;
  }
  virtual void AddUser(std::string account_id) override { users_.push_back(User(account_id)); };
  virtual void UpdateUser(User& user) override {
    for (User& user_ : users_) {
      if (user_.GetAccountId() == user.GetAccountId()) {
        user.isFrozen() ? user_.freeze() : user_.unfreeze();
      }
    }
  };
  virtual User GetExistedUser(std::string account_id) override {
    for (User user_ : users_) {
      if (user_.GetAccountId() == account_id) {
        return user_;
      }
    }
    throw Exception((boost::format("没有找到用户:%1%") % account_id).str());
  }
};

#endif  // TRANSFER_UserRepositoryMock_H
