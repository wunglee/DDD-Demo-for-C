#pragma once

#include <string>

#include "boost/optional.hpp"

#include "exception.h"
#include "user_dto.h"

// 用户服务接口
class UserServiceInterface {
 public:
  virtual ~UserServiceInterface() {}
  virtual void AddUser(const std::string& account_id) = 0;
  virtual void FreezeUser(const std::string& account_id) = 0;
  virtual void UnFreezeUser(const std::string& account_id) = 0;
  virtual bool IsFrozen(const std::string& account_id, bool& is_frozen) = 0;
  virtual boost::optional<UserDTO> GetUser(const std::string& account_id) = 0;
};
