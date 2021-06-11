#pragma once
#include "application/fund_service.h"
#include "backend_adapters/fund_dao.h"
#include "backend_adapters/fund_query.h"
#include "backend_adapters/fund_repository.h"
#include "frontend_adapters/fund_event_monitor.h"

class FundServiceFactory {
 public:
  static FundServiceInterface* GetInstance() {
    return FundService::BuildInstance(
        FundRepository::BuildInstance(FundDAO::BuildInstance()),
        FundQuery::BuildInstance(FundDAO::BuildInstance()));
  }
};
