#include "application/transfer_service.h"
#include "backend_adapters/transfer_query.h"
#include "frontend_adapters/transfer_event_monitor.h"
#include "backend_adapters/transfer_repository.h"
#include "backend_adapters/transfer_menory_dao.h"
#include "frontend_adapters/protobuf_require_adaptor.h"
#include "frontend_adapters/transfer_require_mapping.h"
#include "../../../test/integration_test/transfer_service_factory_for_integration.h"
TransferService * TransferService::transfer_Service_= nullptr;
TransferQuery * TransferQuery::transferQuery_= nullptr;
TransferEventMonitor * TransferEventMonitor::transferEventMonitor_= nullptr;
TransferRepository * TransferRepository::transferRepository_= nullptr;
TransferMenoryDAO * TransferMenoryDAO::transfer_dao_= nullptr;
ProtobufRequireAdaptor * ProtobufRequireAdaptor::protobufRequireAdaptor_= nullptr;
TransferRequireMapping* TransferRequireMapping::transferRequireMapping_= nullptr;
UserServiceInterface* TransferServiceFactoryForIntegration::userServiceInterface_= nullptr;
UserHttpClient* UserHttpClient::user_http_client_= nullptr;

