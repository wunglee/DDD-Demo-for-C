#ifndef TRANSFER_MemoryPublishSubscribeService_H
#define TRANSFER_MemoryPublishSubscribeService_H
#include "boost/optional.hpp"

#include "../naming_service/naming_service_manager.h"
#include "domain_event.h"
#include "event_monitor.h"
#include "publish_subscribe_service_handler.h"

class MemoryPublishSubscribeService : public PublishSubscribeServiceHandler {
 private:
  typedef std::map<std::string, std::vector<std::string>> Monitors;
  Monitors monitors;
  MemoryPublishSubscribeService() {}
  static MemoryPublishSubscribeService* publish_Subscribe_Service;
  void Idempotent_Check(std::string event_name, long requestion_id) {}

 public:
  ~MemoryPublishSubscribeService() {
    MemoryPublishSubscribeService::publish_Subscribe_Service = nullptr;
    monitors.clear();
  }
  static MemoryPublishSubscribeService* BuildInstance() {
    if (publish_Subscribe_Service == nullptr) {
      publish_Subscribe_Service = new MemoryPublishSubscribeService();
    }
    return publish_Subscribe_Service;
  }
  static MemoryPublishSubscribeService* GetInstance() { return BuildInstance(); }
  static void DestoryInstance() { delete MemoryPublishSubscribeService::publish_Subscribe_Service; }
  void Subscribe(std::string event_name, std::string monitor_name) override {
    monitors[event_name].push_back(monitor_name);
  }
  void Publish(DomainEvent domain_Event) override {
    Idempotent_Check(domain_Event.Get_Name(), domain_Event.Get_Transaction_Id());
    /**
     * TODO:需要发布到可靠消息中心，并在另一个线程或进程中异步处理。
     */
    for (std::string monitor_name : monitors[domain_Event.Get_Name()]) {
      boost::optional<EventMonitor*> event_Monitor =
          NamingServiceManager::GetInstance()->Find_Service<EventMonitor*>(monitor_name);
      if (event_Monitor.has_value()) {
        event_Monitor.value()->Handle(domain_Event);
      }
    }
  }
  void ClearMonitors() override { monitors.clear(); }
};

#endif  // TRANSFER_MemoryPublishSubscribeService_H
