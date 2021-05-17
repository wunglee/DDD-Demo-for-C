//
// Created by 王立 on 2021/5/7.
//

#ifndef TRANSFER_事件监听器_H
#define TRANSFER_事件监听器_H
#include "领域事件.h"

class 事件监听器 {
public:
    virtual ~事件监听器(){};
    virtual void 处理(const 领域事件 领域事件_)=0;
};


#endif //TRANSFER_事件监听器_H
