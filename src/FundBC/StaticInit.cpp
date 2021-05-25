#include "Application/FundService.h"
#include "FrontendAdapters/FundEventMapping.h"
#include "BackendAdapters/FundRepository.h"
#include "BackendAdapters/FundDAO.h"
#include "BackendAdapters/FundQuery.h"
FundService * FundService::资金帐户服务_= nullptr;
FundEventMapping * FundEventMapping::资金事件处理器_= nullptr;
FundRepository * FundRepository::资金帐户仓储_= nullptr;
FundDAO* FundDAO::资金帐户DAO_= nullptr;
FundQuery* FundQuery::资金帐户查询服务_= nullptr;