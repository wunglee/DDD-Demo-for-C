#ifndef TRANSFER_UserDAO_H
#define TRANSFER_UserDAO_H
#include "user_dao_interface.h"
#include "user_po.h"
#include <string>
#include <vector>
class UserMenoryDAO : public UserDAOInterface {
 private:
  std::vector<UserPO> userPOs;
  static UserMenoryDAO* userDAO_;

 public:
  ~UserMenoryDAO() {
    userPOs.clear();
      UserMenoryDAO::userDAO_ = nullptr;
  }
  static UserMenoryDAO* BuildInstance() {
    if (UserMenoryDAO::userDAO_ == nullptr) {
        UserMenoryDAO::userDAO_ = new UserMenoryDAO();
    }
    return UserMenoryDAO::userDAO_;
  }
  static UserMenoryDAO* GetInstance() { return BuildInstance(); }
  static void DestroyInstance() {
    if (UserMenoryDAO::userDAO_ != nullptr) delete UserMenoryDAO::userDAO_;
  }
  virtual boost::optional<UserPO> GetUserPO(std::string account_id) override {
    for (UserPO& userPO : userPOs) {
      if (userPO.account_id_ == account_id) {
        return userPO;
      }
    }
    return boost::none;
  }
  virtual void AddUserPO(const UserPO userPO) override { userPOs.push_back(userPO); };
  virtual void UpdateUserPO(const UserPO _userPO) override {
    for (UserPO& userPO_ : userPOs) {
      if (userPO_.account_id_ == _userPO.account_id_) {
        userPO_.frozen_ = _userPO.frozen_;
      }
    }
  };
};
#endif  // TRANSFER_UserDAO_H
