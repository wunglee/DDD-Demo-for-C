//
// Created by 王立 on 2021/5/7.
//

#ifndef TRANSFER_EventMonitor_H
#define TRANSFER_EventMonitor_H
#include "domain_event.h"
class EventMonitor {
public:
    virtual ~EventMonitor(){};
    virtual void Handle(const DomainEvent domainEvent)=0;
};


#endif //TRANSFER_EventMonitor_H
