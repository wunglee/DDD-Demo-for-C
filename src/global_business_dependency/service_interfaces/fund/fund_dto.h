#ifndef TRANSFER_FundDTO_H
#define TRANSFER_FundDTO_H
#include <sstream>
#include <string>
#include <vector>

#include "../../../framework_components/comm_lib/string_helper.h"
#include "../../../framework_components/exception.h"

struct FundDTO {
  const std::string account_id_;
  const bool forbid_in_ = false;
  const bool forbid_out_ = false;
  const float free_amount_ = 0;
  const float locked_amount_ = 0;
  FundDTO(
      const std::string& accountId,
      const bool forbidIn,
      const bool forbidOut,
      const float freeAmount,
      const float lockedAmount)
      : account_id_(accountId),
        forbid_in_(forbidIn),
        forbid_out_(forbidOut),
        free_amount_(freeAmount),
        locked_amount_(lockedAmount) {}
};
struct IncreaseSuccessDTO {
  const int order_no_;
  const std::string account_id_;
  const float amount_;
  IncreaseSuccessDTO(const int order_no, const std::string& account_id, const float amount)
      : order_no_(order_no), account_id_(account_id), amount_(amount) {}

  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << account_id_ << DIVIDER << amount_;

    return ss.str();
  }

  static IncreaseSuccessDTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 3) {
      throw Exception("反序列化IncreaseSuccessDTO失败");
    }
    return IncreaseSuccessDTO(atoi(vec[0].c_str()), vec[1], atof(vec[2].c_str()));
  }
};
struct DecreaseFailDTO {
  const int order_no_;
  Exception exception_;
  DecreaseFailDTO(const int order_no, const Exception& exception)
      : order_no_(order_no), exception_(exception) {}

  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << exception_.getMessage();
    return ss.str();
  }

  static DecreaseFailDTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 2) {
      throw Exception("反序列化DecreaseFailDTO失败");
    }
    return DecreaseFailDTO(atoi(vec[0].c_str()), Exception(vec[1]));
  }
};
struct IncreaseFailDTO {
  const int order_no_;
  Exception exception_;
  IncreaseFailDTO(const int order_no, const Exception& exception)
      : order_no_(order_no), exception_(exception) {}

  // TODO DTO使用PROTOBUF实现
  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << exception_.getMessage();
    return ss.str();
  }

  static IncreaseFailDTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 2) {
      throw Exception("反序列化IncreaseFailDTO失败");
    }
    return IncreaseFailDTO(atoi(vec[0].c_str()), Exception(vec[1]));
  }
};
struct LockAmountDTO {
  const std::string order_no_;
  const std::string account_id_;
  const float amount_;
  LockAmountDTO(const std::string& order_no, const std::string& account_id, const float amount)
      : order_no_(order_no), account_id_(account_id), amount_(amount) {}
};

#endif  // TRANSFER_FundDTO_H
