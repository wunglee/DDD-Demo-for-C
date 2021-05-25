//
// Created by 王立 on 2021/5/7.
//

#ifndef TRANSFER_事件监听器_H
#define TRANSFER_事件监听器_H
#include "DomainEvent.h"

class EventMonitor {
public:
    virtual ~EventMonitor(){};
    virtual void 处理(const DomainEvent 领域事件_)=0;
};


#endif //TRANSFER_事件监听器_H
