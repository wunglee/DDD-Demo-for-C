#ifndef TRANSFER_EventMonitorMock_H
#define TRANSFER_EventMonitorMock_H
#include "../../../src/framework_components/domain_event/event_monitor.h"

class EventMonitorMock : public EventMonitor{
private:
    bool result=false;
public:
    virtual void Handle(const DomainEvent domainEvent) override{
        if("转账已创建"== domainEvent.Get_Name()){
            result=true;
        }
    }
    bool getResult(){
        return result;
    }
};


#endif //TRANSFER_EventMonitorMock_H
