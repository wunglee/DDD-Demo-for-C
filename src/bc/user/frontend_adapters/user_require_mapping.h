#ifndef TRANSFER_UserRequireMapping_H
#define TRANSFER_UserRequireMapping_H
#include "boost/any.hpp"

#include "../../../framework_components/naming_service/naming_service_manager.h"
#include "../../../framework_components/requestion_filters/require_mapping.h"
#include "../../../framework_components/requestion_filters/response.h"
#include "../../../global_business_dependency/service_interfaces/user/user_dto.h"
#include "../../../global_business_dependency/service_interfaces/user/user_service_interface.h"
class UserRequireMapping : public RequireMapping {
 private:
  UserServiceInterface* userServiceInterface_;
  static UserRequireMapping* userRequireMapping_;
  UserRequireMapping(UserServiceInterface* userServiceInterface_)
      : userServiceInterface_(userServiceInterface_) {}

 public:
  virtual ~UserRequireMapping() { UserRequireMapping::userRequireMapping_ = nullptr; }
  static UserRequireMapping* BuildInstance(UserServiceInterface* userServiceInterface) {
    if (UserRequireMapping::userRequireMapping_ == nullptr) {
      UserRequireMapping::userRequireMapping_ = new UserRequireMapping(userServiceInterface);
    }
    return UserRequireMapping::userRequireMapping_;
  }
  static UserRequireMapping* GetInstance() {
    if (UserRequireMapping::userRequireMapping_ == nullptr) {
      throw "单例未构建";
    }
    return UserRequireMapping::userRequireMapping_;
  }
  static void DestroyInstance() {
    if (UserRequireMapping::userRequireMapping_ != nullptr) {
      delete UserRequireMapping::userRequireMapping_;
    }
  }
  // TODO:太多if，待重构
  virtual Response handle(std::string function_name, const boost::any& parameters) override {
    Response response;
    if (function_name == "create_user") {
      UserDTO userDTO = boost::any_cast<UserDTO>(parameters);
      userServiceInterface_->AddUser(userDTO.account_id_);
    } else if (function_name == "FreezeUser") {
      UserDTO userDTO = boost::any_cast<UserDTO>(parameters);
      userServiceInterface_->FreezeUser(userDTO.account_id_);
    } else if (function_name == "UnfreezeUser") {
      UserDTO userDTO = boost::any_cast<UserDTO>(parameters);
      userServiceInterface_->UnfreezeUser(userDTO.account_id_);
    } else if (function_name == "GetUser") {
      UserDTO userDTO = boost::any_cast<UserDTO>(parameters);
      boost::optional<UserDTO> user_optional = userServiceInterface_->GetUser(userDTO.account_id_);
      response.value = user_optional;
    } else if (function_name == "IsFrozen") {
      UserDTO userDTO = boost::any_cast<UserDTO>(parameters);
      bool frozen = userServiceInterface_->IsFrozen(userDTO.account_id_);
      response.value = frozen;
    } else {
      throw Exception("未知的function_name");
    }

    return response;
  }
};

#endif  // TRANSFER_UserRequireMapping_H
