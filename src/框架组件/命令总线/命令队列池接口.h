//
// Created by 王立 on 2021/5/15.
//

#ifndef TRANSFER_命令队列池接口_H
#define TRANSFER_命令队列池接口_H
#include "命令.h"
#include "boost/optional.hpp"
class 命令队列池接口 {
public:
    virtual ~命令队列池接口(){}
    virtual void 加入命令(命令& 命令)=0;
    virtual boost::optional<命令> 取出命令()=0;
};


#endif //TRANSFER_命令队列池接口_H
