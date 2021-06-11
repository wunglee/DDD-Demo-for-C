#ifndef TRANSFER_TransferFrontendEnvironment_H
#define TRANSFER_TransferFrontendEnvironment_H
#include "gtest/gtest.h"
#include "../../../../src/bc/transfer/frontend_adapters/transfer_require_mapping.h"
#include "../../../../src/framework_components/requestion_filters/requestion_configure.h"
#include "tansfer_service_mock.h"
#include "../../../../src/bc/transfer/frontend_adapters/protobuf_require_adaptor.h"
class TransferFrontendEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::GetInstance()->Add_Require_Mapping("TransferRequireMapping",
                                                         TransferRequireMapping::BuildInstance(TansferServiceMock::GetInstance()));
        NamingServiceManager::GetInstance()->Add_Service<ProtobufRequireAdaptor *>("ProtobufRequireAdaptor",
                                                                                     ProtobufRequireAdaptor::BuildInstance(
                                                                                             RequireInterceptor::GetInstance()));
    }
    virtual void TearDown() {
        RequestionConfigure::DestroyInstance();
        TransferRequireMapping::DestroyInstance();
        TansferServiceMock::DestroyInstance();
        ProtobufRequireAdaptor::DestroyInstance();
        NamingServiceManager::Destroy_Singleton();
        RequireInterceptor::Destroy_Singleton();
    }
};
#endif //TRANSFER_TransferFrontendEnvironment_H
