#ifndef TRANSFER_FundServiceFactory_H
#define TRANSFER_FundServiceFactory_H
#include "../../src/bc/fund/application/fund_service.h"
#include "../../src/bc/fund/backend_adapters/fund_repository.h"
#include "../../src/bc/fund/backend_adapters/fund_query.h"
#include "../../src/bc/fund/backend_adapters/fund_menory_dao.h"
#include "../../src/bc/fund/frontend_adapters/fund_event_monitor.h"
#include "../../src/bc/fund/fund_service_factory.h"

class FundServiceFactoryForIntegration{
public:
    static FundServiceLocalInterface *GetInstance() {
        return FundServiceFactory::GetInstance(FundMenoryDAO::GetInstance());
    }
    static void DestroyInstance() {
        return FundServiceFactory::DestroyInstance();
    }
};
#endif //TRANSFER_FundServiceFactory_H
