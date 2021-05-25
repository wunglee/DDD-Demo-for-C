#ifndef TRANSFER_事件监听器模拟_H
#define TRANSFER_事件监听器模拟_H
#include "../../src/FrameworkComponents/DomainEvent/EventMonitor.h"

class EventMonitorMock : public EventMonitor{
private:
    bool 处理结果=false;
public:
    virtual void 处理(const DomainEvent 领域事件_) override{
        if("转账已创建"==领域事件_.获取事件名()){
            处理结果=true;
        }
    }
    bool 获取处理结果(){
        return 处理结果;
    }
};


#endif //TRANSFER_事件监听器模拟_H
