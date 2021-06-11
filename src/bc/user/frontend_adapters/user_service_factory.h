//
// Created by 王立 on 2021/5/17.
//

// #pragma once
// #include "application/user_service.h"
// #include "backend_adapters/user_dao.h"
// #include "backend_adapters/user_query.h"
// #include "backend_adapters/user_repository.h"
// #include "frontend_adapters/user_require_mapping.h"
// #include "requestion_filters/require_mappings_manager.h"

// class UserServiceFactory {
//  public:
//   static UserServiceInterface* GetInstance() {
//     return UserService::BuildInstance(
//         UserRepository::BuildInstance(UserDAO::BuildInstance()),
//         UserQuery::BuildInstance(UserDAO::BuildInstance()));
//   }

//   static void RegistService() {
//     RequireMappingsManager::GetInstance()->RegistRequireMapping(
//         "UserRequireMapping",
//         UserRequireMapping::BuildInstance(UserServiceFactory::GetInstance()));
//   }
// };
