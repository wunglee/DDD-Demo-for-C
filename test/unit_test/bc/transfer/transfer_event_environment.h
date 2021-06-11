#ifndef TRANSFER_TransferEventEnvironment_H
#define TRANSFER_TransferEventEnvironment_H
#include "gtest/gtest.h"
#include "../../../../src/bc/transfer/frontend_adapters/transfer_event_monitor.h"
#include "../../../../src/global_business_dependency/service_interfaces/transfer/transfer_service_interface.h"
#include "../../../../src/framework_components/naming_service/naming_service_manager.h"
#include "../../../../src/framework_components/domain_event/event_monitor.h"
#include "../../../../src/framework_components/requestion_filters/require_interceptor.h"
#include "tansfer_service_mock.h"
#include "../../../../src/framework_components/requestion_filters/requestion_configure.h"
#include "../../../../src/bc/user/frontend_adapters/user_require_mapping.h"
#include "../../../integration_test/transfer_service_factory_for_integration.h"
#include "../../../../src/bc/transfer/frontend_adapters/transfer_require_mapping.h"

class TransferEventEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::GetInstance()->Add_Require_Mapping("TransferRequireMapping", TransferRequireMapping::BuildInstance(TansferServiceMock::GetInstance()));
        NamingServiceManager::GetInstance()->Add_Service("TransferService",
                                                           (TransferServiceInterface *) TansferServiceMock::GetInstance());
        NamingServiceManager::GetInstance()->Add_Service("TransferEventMonitor",
                                                           (EventMonitor *) TransferEventMonitor::BuildInstance(RequireInterceptor::BuildInstance()));
        PublishSubscribeService::BuildInstance()->Subscribe("增资已成功", "TransferEventMonitor");
        PublishSubscribeService::BuildInstance()->Subscribe("增资已失败", "TransferEventMonitor");
        PublishSubscribeService::BuildInstance()->Subscribe("扣减已成功", "TransferEventMonitor");
        PublishSubscribeService::BuildInstance()->Subscribe("扣减已失败", "TransferEventMonitor");
    }
    virtual void TearDown() {
        delete NamingServiceManager::GetInstance()->Remove_Service<EventMonitor *>("TransferEventMonitor").value();
        delete NamingServiceManager::GetInstance()->Remove_Service<TransferServiceInterface *>("TransferService").value();
        NamingServiceManager::Destroy_Singleton();
        PublishSubscribeService::DestoryInstance();
        RequireInterceptor::Destroy_Singleton();
        RequestionConfigure::DestroyInstance();
        TransferRequireMapping::DestroyInstance();
    }
};
#endif //TRANSFER_TransferEventEnvironment_H
