#ifndef TRANSFER_UserServiceFactory_H
#define TRANSFER_UserServiceFactory_H
#include "../../src/bc/user/application/user_service.h"
#include "../../src/bc/user/backend_adapters/user_menory_dao.h"
#include "../../src/bc/user/backend_adapters/user_query.h"
#include "../../src/bc/user/backend_adapters/user_repository.h"
#include "../../src/bc/user/frontend_adapters/user_require_mapping.h"
#include "../../src/framework_components/requestion_filters/require_mappings_manager.h"
#include "../../src/bc/user/UserServiceFactory.h"

class UserServiceFactoryForIntegration {
public:
    static UserServiceInterface *GetInstance() {
        return UserServiceFactory::GetInstance(UserMenoryDAO::GetInstance());
    }

    static void DestroyInstance() {
        UserServiceFactory::DestroyInstance();
    }
};

#endif  // TRANSFER_UserServiceFactory_H
