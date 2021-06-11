#include "application/user_service.h"
#include "frontend_adapters/user_event_monitor.h"
#include "backend_adapters/user_repository.h"
#include "backend_adapters/user_menory_dao.h"
#include "backend_adapters/user_query.h"
#include "frontend_adapters/user_http_service.h"
#include "frontend_adapters/user_require_mapping.h"

UserEventMonitor * UserEventMonitor::userEventMonitor_ = nullptr;
UserRequireMapping* UserRequireMapping::userRequireMapping_= nullptr;
 UserService * UserService::userService_ = nullptr;
 UserQuery * UserQuery::userQuery_ = nullptr;
 UserRepository* UserRepository::userRepository_ = nullptr;
 UserMenoryDAO* UserMenoryDAO::userDAO_ = nullptr;
 UserHttpService * UserHttpService::userHttpService_= nullptr;