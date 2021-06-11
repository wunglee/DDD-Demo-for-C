#pragma once

#include "backend_adapters/user_po.h"
#include "domain/user.h"

class UserConverter {
 public:
  static UserPO ConvertUser2PO(const User& user) {
    UserPO user_po(user.GetAccountId(), user.IsFrozen());

    return user_po;
  }

  static User BuildUserFromPO(const UserPO& user_po) {
    User user(user_po.account_id, user_po.is_freeze);
    return user;
  }
};
