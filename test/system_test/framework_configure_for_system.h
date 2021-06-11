#ifndef PRODUCT_FRAMEWORK_CONFIGURE_
#define PRODUCT_FRAMEWORK_CONFIGURE_

#include "src/framework_components/domain_event/mysql_publish_subscribe_service.h"
#include "src/framework_components/domain_event/publish_subscribe_service.h"
#include "src/framework_components/idempotent/mysql_idempotent_manager.h"
#include "src/framework_components/local_transaction/mysql_transaction_manager.h"
#include "src/framework_components/requestion_filters/require_interceptor.h"

class FrameWorkConfigure {
 public:
  static void ConfigureFrameWork(std::shared_ptr<dalset::CMySqlStorage> connection) {
    RequireInterceptor::BuildInstance(
        MysqlTransactionManager::BuildInstance(connection),
        MysqlIdempotentManager::BuildInstance(connection));
    PublishSubscribeService::BuildInstance(
            MysqlPublishSubscribeService::BuildInstance(connection));
  }
};

#endif
