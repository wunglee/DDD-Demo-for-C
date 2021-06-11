#ifndef TRANSFER_UserEventMonitor_H
#define TRANSFER_UserEventMonitor_H
#include "../../../framework_components/domain_event/event_monitor.h"
//从事件队列中取出事件进行处理
class UserEventMonitor : public EventMonitor {
private:
    static UserEventMonitor *userEventMonitor_;
    UserEventMonitor() {}
public:
    ~UserEventMonitor() {
        UserEventMonitor::userEventMonitor_ = nullptr;
    }
    static UserEventMonitor *BuildInstance() {
        if (userEventMonitor_ == nullptr) {
            userEventMonitor_ = new UserEventMonitor();
        }
        return userEventMonitor_;
    }
    void Handle(const DomainEvent domainEvent){
    }
};


#endif //TRANSFER_UserEventMonitor_H
