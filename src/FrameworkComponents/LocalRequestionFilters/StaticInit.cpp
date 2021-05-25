#include "RequireAccepter.h"
#include "RequestionConfigure.h"

RequiresQueuePool * RequiresQueuePool::请求队列池_= nullptr;
RequireAccepter * RequireAccepter::请求接收器_= nullptr;
RequireMappingsManager * RequireMappingsManager::请求处理器管理器_= nullptr;
RequestionConfigure* RequestionConfigure::请求处理配置器_= nullptr;