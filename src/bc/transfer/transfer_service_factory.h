//
// Created by 王立 on 2021/6/10.
//

#ifndef DDD_DEMO_FOR_C_TRANSFER_SERVICE_FACTORY_H
#define DDD_DEMO_FOR_C_TRANSFER_SERVICE_FACTORY_H


#include "backend_adapters/transfer_repository.h"
#include "backend_adapters/transfer_menory_dao.h"
#include "application/transfer_service.h"
#include "backend_adapters/transfer_query.h"
#include "../../global_business_dependency/service_interfaces/user/user_http_client.h"
#include "../../global_business_dependency/service_interfaces/fund/fund_http_client.h"

class TransferServiceFactory {

public:
    static TransferServiceInterface *GetInstance(TransferDAOInterface *transferDAOInterface) {
        TransferRepositoryInterface * transferRepositoryInterface
        = TransferRepository::BuildInstance(transferDAOInterface,
                                            UserHttpClient::GetInstance());
        TransferQueryInterface * transferQueryInterface
        = TransferQuery::BuildInstance(transferDAOInterface,
                                       UserHttpClient::GetInstance());
        return TransferService::BuildInstance(transferRepositoryInterface,
                                              transferQueryInterface,
                                              UserHttpClient::GetInstance(),
                                              FundHttpClient::GetInstance());
    }

    static void DestroyInstance() {
        UserHttpClient::DestroyInstance();
        TransferMenoryDAO::DestroyInstance();
        TransferRepository::DestroyInstance();
        TransferQuery::DestroyInstance();
        TransferService::DestroySingleton();
        FundHttpClient::Destroy_Singleton();
    }
};


#endif //DDD_DEMO_FOR_C_TRANSFER_SERVICE_FACTORY_H
