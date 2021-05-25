#include "Application/TransferService.h"
#include "BackendAdapters/TransferQuery.h"
#include "FrontendAdapters/TransferEventMonitor.h"
#include "BackendAdapters/TransferRepository.h"
#include "BackendAdapters/TransferDAO.h"
#include "FrontendAdapters/ProtobufRequireAdaptor.h"
#include "FrontendAdapters/TransferRequireMapping.h"
#include "TransferServiceFactory.h"
TransferService * TransferService::转账服务_= nullptr;
TransferQuery * TransferQuery::转账查询_= nullptr;
TransferEventMonitor * TransferEventMonitor::转账事件处理器_= nullptr;
TransferRepository * TransferRepository::转账仓储_= nullptr;
TransferDAO * TransferDAO::转账DAO_= nullptr;
ProtobufRequireAdaptor * ProtobufRequireAdaptor::PB请求适配器_= nullptr;
TransferRequireMapping* TransferRequireMapping::转账请求处理器_= nullptr;
UserServiceInterface* TransferServiceFactory::用户服务接口_= nullptr;
UserHttpClient* UserHttpClient::用户HTTP客户端_= nullptr;