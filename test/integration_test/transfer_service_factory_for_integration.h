#ifndef TRANSFER_TransferServiceFactory_H
#define TRANSFER_TransferServiceFactory_H
#include "../../src/bc/transfer/backend_adapters/transfer_repository.h"
#include "../../src/bc/transfer/backend_adapters/transfer_menory_dao.h"
#include "../../src/bc/transfer/application/transfer_service.h"
#include "../../src/bc/transfer/backend_adapters/transfer_query.h"
#include "../../src/global_business_dependency/service_interfaces/user/user_http_client.h"
#include "../../src/global_business_dependency/service_interfaces/fund/fund_http_client.h"
#include "../../src/bc/transfer/transfer_service_factory.h"

class TransferServiceFactoryForIntegration{
public:
    static UserServiceInterface* userServiceInterface_;
    static TransferServiceInterface *GetInstance(){
        return TransferServiceFactory::GetInstance(TransferMenoryDAO::BuildInstance());
    }
    static void DestroyInstance(){
        return TransferServiceFactory::DestroyInstance();
    }
};


#endif //TRANSFER_TransferServiceFactory_H
