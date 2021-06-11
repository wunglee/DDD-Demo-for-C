//
// Created by 王立 on 2021/6/10.
//

#ifndef DDD_DEMO_FOR_C_USERSERVICEFACTORY_H
#define DDD_DEMO_FOR_C_USERSERVICEFACTORY_H


#include "application/user_service.h"
#include "backend_adapters/user_menory_dao.h"
#include "backend_adapters/user_query.h"
#include "backend_adapters/user_repository.h"
#include "frontend_adapters/user_require_mapping.h"
#include "../../framework_components/requestion_filters/require_mappings_manager.h"

class UserServiceFactory {

public:
    static UserServiceInterface *GetInstance(UserMenoryDAO *userDAOInterface) {
        return UserService::BuildInstance(
          UserRepository::BuildInstance(userDAOInterface),
          UserQuery::BuildInstance(userDAOInterface));
    }

    static void DestroyInstance() {
      UserMenoryDAO::DestroyInstance();
      UserRepository::DestroyInstance();
      UserQuery::DestroyInstance();
      UserService::DestroyInstance();
    }
};


#endif //DDD_DEMO_FOR_C_USERSERVICEFACTORY_H
