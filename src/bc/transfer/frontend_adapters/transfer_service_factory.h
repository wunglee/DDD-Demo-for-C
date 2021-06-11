#pragma once
#include "application/transfer_service.h"
#include "backend_adapters/transfer_dao.h"
#include "backend_adapters/transfer_query.h"
#include "backend_adapters/transfer_repository.h"
#include "frontend_adapters/user_http_service.h"
#include "frontend_adapters/user_require_mapping.h"
#include "frontend_adapters/user_service_factory.h"
#include "requestion_filters/require_mappings_manager.h"
#include "user_http_client.h"

class TransferServiceFactory {
 public:
  static UserServiceInterface* user_service_interface_;
  static TransferServiceInterface* GetInstance() {
    RequireMappingsManager::GetInstance()->RegistRequireMapping(
        "UserRequireMapping", UserRequireMapping::BuildInstance(UserServiceFactory::GetInstance()));
    UserHttpClient* user_http_client_ = UserHttpClient::BuildInstance(
        UserHttpService::BuildInstance(RequireMappingsManager::GetInstance()));

    return TransferService::BuildInstance(
        TransferRepository::BuildInstance(TransferDAO::BuildInstance(), user_http_client_),
        TransferQuery::BuildInstance(TransferDAO::BuildInstance(), user_http_client_),
        user_http_client_);
  }
};
