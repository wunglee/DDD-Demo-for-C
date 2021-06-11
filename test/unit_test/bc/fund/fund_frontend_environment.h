#pragma once

#include "gtest/gtest.h"

#include "domain_event/event_monitor.h"
#include "domain_event/publish_subscribe_service.h"
#include "frontend_adapters/fund_event_monitor.h"
#include "fund_service_mock.h"
// #include "service_interfaces/fund_service_interface.h"

class FundFrontendEnvironment : public ::testing::Test {
 public:
  FundServiceMock* fund_service_ = FundServiceMock::GetInstance();
  virtual void SetUp() {
    PublishSubscribeService::BuildInstance()->Subscribe(
        "TransferCreated", FundEventMonitor::BuildInstance(FundServiceMock::GetInstance()));
    PublishSubscribeService::BuildInstance()->Subscribe(
        "UserCreated", FundEventMonitor::BuildInstance(FundServiceMock::GetInstance()));
    PublishSubscribeService::BuildInstance()->Subscribe(
        "TransferOutFinish", FundEventMonitor::BuildInstance(FundServiceMock::GetInstance()));
    PublishSubscribeService::BuildInstance()->Subscribe(
        "TransferRefunding", FundEventMonitor::BuildInstance(FundServiceMock::GetInstance()));
  }
  virtual void TearDown() {}
};
