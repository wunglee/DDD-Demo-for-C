#ifndef TRANSFER_USERDTO_H
#define TRANSFER_USERDTO_H
#include <string>

#include "../../../framework_components/comm_lib/string_helper.h"

// static const char DIVIDER[] = "|||";

struct UserCreatedDTO {
  const std::string account_id_;
  UserCreatedDTO(const std::string account_id) : account_id_(account_id) {}

  std::string Serialize() { return account_id_; }

  static UserCreatedDTO Unserialize(const std::string& str) { return UserCreatedDTO(str); }
};
struct UserDTO {
  const std::string account_id_;
  const bool is_frozen_;
  UserDTO(const std::string account_id, const bool is_frozen = false)
      : account_id_(account_id), is_frozen_(is_frozen) {}
};

#endif  // TRANSFER_USERDTO_H
