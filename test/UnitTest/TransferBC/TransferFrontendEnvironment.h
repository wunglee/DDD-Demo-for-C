#ifndef TRANSFER_主适配器请求测试环境_H
#define TRANSFER_主适配器请求测试环境_H
#include "gtest/gtest.h"
#include "../../../src/TransferBC/FrontendAdapters/TransferRequireMapping.h"
#include "../../../src/FrameworkComponents/RequestionFilters/RequestionConfigure.h"
#include "TansferServiceMock.h"
#include "../../../src/TransferBC/FrontendAdapters/ProtobufRequireAdaptor.h"
class TransferFrontendEnvironment : public ::testing::Test {
public:
    virtual void SetUp() {
        RequestionConfigure::获取单例()->注册请求处理器("TransferRequireMapping", TransferRequireMapping::构建单例(TansferServiceMock::获取单例()));
        NamingServiceManager::获取单例()->注册服务<ProtobufRequireAdaptor *>("ProtobufRequireAdaptor", ProtobufRequireAdaptor::构建单例(RequireInterceptor::获取单例()));
    }
    virtual void TearDown() {
        RequestionConfigure::销毁单例();
        TransferRequireMapping::销毁单例();
        TansferServiceMock::销毁单例();
        ProtobufRequireAdaptor::销毁单例();
        NamingServiceManager::销毁单例();
    }
};
#endif //TRANSFER_主适配器请求测试环境_H
