#ifndef TRANSFER_UserServiceInterface_H
#define TRANSFER_UserServiceInterface_H

#include "boost/optional.hpp"

#include "../../../bc/user/domain/user.h"
#include "../../../global_business_dependency/service_interfaces/user/user_dto.h"
class UserServiceInterface {
 public:
  virtual ~UserServiceInterface() {}
  virtual void AddUser(std::string account_name) = 0;
  virtual void FreezeUser(std::string account_name) = 0;
  virtual void UnfreezeUser(std::string account_name) = 0;
  virtual bool IsFrozen(std::string account_name) = 0;
  virtual boost::optional<UserDTO> GetUser(std::string account_name) = 0;
};

#endif  // TRANSFER_UserServiceInterface_H
