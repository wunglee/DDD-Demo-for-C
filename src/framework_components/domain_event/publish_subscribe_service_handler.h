#pragma once
#include <string>

#include "domain_event.h"

// 事件发布订阅服务
class PublishSubscribeServiceHandler {
 public:
  virtual ~PublishSubscribeServiceHandler() {}

 public:
  virtual void Publish(DomainEvent domain_Event) = 0;
  virtual void Subscribe(std::string event_name, std::string monitor_name) = 0;
  virtual void ClearMonitors() = 0;
};
