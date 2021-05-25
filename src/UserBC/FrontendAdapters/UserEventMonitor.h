#ifndef TRANSFER_用户事件处理器_H
#define TRANSFER_用户事件处理器_H
#include "../../FrameworkComponents/DomainEvent/EventMonitor.h"
//从事件队列中取出事件进行处理
class UserEventMonitor : public EventMonitor {
private:
    static UserEventMonitor *用户事件处理器_;
    UserEventMonitor() {}
public:
    ~UserEventMonitor() {
        UserEventMonitor::用户事件处理器_ = nullptr;
    }
    static UserEventMonitor *构建单例() {
        if (用户事件处理器_ == nullptr) {
            用户事件处理器_ = new UserEventMonitor();
        }
        return 用户事件处理器_;
    }
    void 处理(const DomainEvent 领域事件_){
    }
};


#endif //TRANSFER_用户事件处理器_H
