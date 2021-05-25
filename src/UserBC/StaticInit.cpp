#include "Application/UserService.h"
#include "FrontendAdapters/UserEventMonitor.h"
#include "BackendAdapters/UserRepository.h"
#include "BackendAdapters/UserDAO.h"
#include "BackendAdapters/UserQuery.h"
#include "FrontendAdapters/UserHttpService.h"
#include "FrontendAdapters/UserRequireMapping.h"

UserEventMonitor * UserEventMonitor::用户事件处理器_ = nullptr;
UserRequireMapping* UserRequireMapping::用户请求处理器_= nullptr;
 UserService * UserService::用户服务_ = nullptr;
 UserQuery * UserQuery::用户查询_ = nullptr;
 UserRepository* UserRepository::用户仓储_ = nullptr;
 UserDAO* UserDAO::单例_ = nullptr;
 UserHttpService * UserHttpService::用户HTTP服务端_= nullptr;