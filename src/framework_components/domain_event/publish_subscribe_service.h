#ifndef TRANSFER_PublishSubscribeService_H
#define TRANSFER_PublishSubscribeService_H
#include "boost/optional.hpp"

#include "../naming_service/naming_service_manager.h"
#include "domain_event.h"
#include "event_monitor.h"
#include "memory_publish_subscribe_service.h"

class PublishSubscribeService {
 private:
  PublishSubscribeServiceHandler* publish_subscribe_service_handler_ = nullptr;
  PublishSubscribeService(PublishSubscribeServiceHandler* publish_subscribe_service_handler):publish_subscribe_service_handler_(publish_subscribe_service_handler) {}

  static PublishSubscribeService* publish_Subscribe_Service;

 public:
  ~PublishSubscribeService() { PublishSubscribeService::publish_Subscribe_Service = nullptr; }
  static PublishSubscribeService* BuildInstance(
      PublishSubscribeServiceHandler* publish_subscribe_service_handler = nullptr) {
    if (publish_Subscribe_Service == nullptr) {
      if (publish_subscribe_service_handler == nullptr) {
        publish_subscribe_service_handler = MemoryPublishSubscribeService::BuildInstance();
      }

      publish_Subscribe_Service = new PublishSubscribeService(publish_subscribe_service_handler);
    }
    return publish_Subscribe_Service;
  }
  static PublishSubscribeService* GetInstance() { return BuildInstance(); }
  static void DestoryInstance() { delete PublishSubscribeService::publish_Subscribe_Service; }
  void Subscribe(std::string event_name, std::string monitor_name) {
    publish_subscribe_service_handler_->Subscribe(event_name, monitor_name);
  }
  void Publish(DomainEvent domain_Event) {
    publish_subscribe_service_handler_->Publish(domain_Event);
  }

  void ClearMonitors() { publish_subscribe_service_handler_->ClearMonitors(); }
};

#endif  // TRANSFER_PublishSubscribeService_H
