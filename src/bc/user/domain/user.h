#ifndef ARGS_User_H
#define ARGS_User_H
#include "../../fund/application/fund_service.h"
class User {
 private:
  std::string account_id_;
  bool frozen_;

 public:
  User(const std::string& account_id, bool frozen = false)
      : account_id_(account_id), frozen_(frozen) {}

  const std::string GetAccountId() const { return account_id_; }
  void freeze() { frozen_ = true; }
  void unfreeze() { frozen_ = false; }
  bool isFrozen() const { return frozen_; }
};

#endif  // ARGS_User_H
