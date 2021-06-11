//
// Created by 王立 on 2021/6/10.
//

#ifndef DDD_DEMO_FOR_C_FUND_SERVICE_FACTORY_H
#define DDD_DEMO_FOR_C_FUND_SERVICE_FACTORY_H


#include "application/fund_service.h"
#include "backend_adapters/fund_repository.h"
#include "backend_adapters/fund_query.h"
#include "backend_adapters/fund_menory_dao.h"
#include "frontend_adapters/fund_event_monitor.h"

class FundServiceFactory {
public:
    static FundServiceLocalInterface *GetInstance(FundMenoryDAO *fundDaoInterface) {
        FundRepositoryInterface * fundRepositoryInterface
           = FundRepository::BuildInstance(fundDaoInterface);
        FundServiceQueryInterface * fundServiceQueryInterface
            = FundQuery::BuildInstance(fundDaoInterface);
        return FundService::BuildInstance(fundRepositoryInterface, fundServiceQueryInterface);
    }

    static void DestroyInstance(){
         FundMenoryDAO::DestroyInstance();
         FundRepository::DestroyInstance();
         FundQuery::DestroyInstance();
         FundService::DestoryInstance();
    }
};


#endif //DDD_DEMO_FOR_C_FUND_SERVICE_FACTORY_H
