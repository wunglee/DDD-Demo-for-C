#include "application/fund_service.h"
#include "frontend_adapters/fund_event_monitor.h"
#include "backend_adapters/fund_repository.h"
#include "backend_adapters/fund_menory_dao.h"
#include "backend_adapters/fund_query.h"
#include "frontend_adapters/fund_require_mapping.h"
#include "frontend_adapters/fund_http_service.h"
#include "../../global_business_dependency/service_interfaces/fund/fund_http_client.h"

FundService * FundService::fund_Service= nullptr;
FundEventMonitor * FundEventMonitor::fund_event_mapping_= nullptr;
FundRepository * FundRepository::fundRepository_= nullptr;
FundMenoryDAO* FundMenoryDAO::fundDao_= nullptr;
FundQuery* FundQuery::fundQuery_= nullptr;
FundRequireMapping * FundRequireMapping::fund_require_mapping_= nullptr;
FundHttpService * FundHttpService::fundHttpService= nullptr;
FundHttpClient* FundHttpClient::fundHttpClient= nullptr;