#ifndef TRANSFER_TransferDTO_H
#define TRANSFER_TransferDTO_H
#include <sstream>
#include <string>

#include "../../../framework_components/comm_lib/string_helper.h"

struct TransferDTO {
  const int order_no_;
  const std::string payer_account_;
  const std::string payee_account_;
  const float amount_;
  const int status_;
  TransferDTO(
      const int orderNo,
      const std::string& payerAccount,
      const std::string& payeeAccount,
      const float amount,
      const int status)
      : order_no_(orderNo),
        payer_account_(payerAccount),
        payee_account_(payeeAccount),
        amount_(amount),
        status_(status) {}
};
struct ApplyTransferDTO {
  const std::string payer_account_;
  const std::string payee_account_;
  const float amount_;
  ApplyTransferDTO(const std::string& payer_account, const std::string& payee_account, float amount)
      : payer_account_(payer_account), payee_account_(payee_account), amount_(amount) {}
};

struct Refund_Created_DTO {
  const int order_no_;
  const std::string payer_account_;
  const float amount_;
  Refund_Created_DTO(const int order_no, const std::string payer_account, float amount)
      : order_no_(order_no), payer_account_(payer_account), amount_(amount) {}

  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << payer_account_ << DIVIDER << amount_;

    return ss.str();
  }

  static Refund_Created_DTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 3) {
      throw Exception("反序列化Refund_Created_DTO失败");
    }
    return Refund_Created_DTO(atoi(vec[0].c_str()), vec[1], atof(vec[2].c_str()));
  }
};
struct Payer_Deducted_DTO {
  const int order_no_;
  const std::string payee_account_;
  const float amount_;
  Payer_Deducted_DTO(const int order_no, const std::string payee_account_, float amount)
      : order_no_(order_no), payee_account_(payee_account_), amount_(amount) {}

  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << payee_account_ << DIVIDER << amount_;

    return ss.str();
  }

  static Payer_Deducted_DTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 3) {
      throw Exception("反序列化Payer_Deducted_DTO失败");
    }
    return Payer_Deducted_DTO(atoi(vec[0].c_str()), vec[1], atof(vec[2].c_str()));
  }
};

struct Payee_Increased_DTO {
  const int order_no_;
  const std::string payer_;
  const std::string payee_;
  const float amount_;
  Payee_Increased_DTO(
      const int order_no, const std::string& payer, const std::string& payee, const float amount)
      : order_no_(order_no), payer_(payer), payee_(payee), amount_(amount) {}

  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << payer_ << DIVIDER << payee_ << DIVIDER << amount_;

    return ss.str();
  }

  static Payee_Increased_DTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 4) {
      throw Exception("反序列化IncreaseSuccessDTO失败");
    }
    return Payee_Increased_DTO(atoi(vec[0].c_str()), vec[1], vec[2], atof(vec[3].c_str()));
  }
};
struct Refund_DTO {
  const int order_no_;
  const std::string payer_account_;
  const float amount_;
  Refund_DTO(const int order_no, const std::string& payer_account, const float amount)
      : order_no_(order_no), payer_account_(payer_account), amount_(amount) {}

  std::string Serialize() {
    std::stringstream ss;
    ss << order_no_ << DIVIDER << payer_account_ << DIVIDER << amount_;

    return ss.str();
  }

  static Refund_DTO Unserialize(const std::string& str) {
    std::vector<std::string> vec;
    SplitStringIntoVector(str.c_str(), DIVIDER, vec);
    if (vec.size() != 3) {
      throw Exception("反序列化Refund_DTO失败");
    }
    return Refund_DTO(atoi(vec[0].c_str()), vec[1], atof(vec[2].c_str()));
  }
};
#endif  // TRANSFER_TransferDTO_H
