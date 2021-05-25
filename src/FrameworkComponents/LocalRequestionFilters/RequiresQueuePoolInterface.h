//
// Created by 王立 on 2021/5/15.
//

#ifndef TRANSFER_请求队列池接口_H
#define TRANSFER_请求队列池接口_H
#include "Require.h"
#include "boost/optional.hpp"
class RequiresQueuePoolInterface {
public:
    virtual ~RequiresQueuePoolInterface(){}
    virtual void 加入请求(Require& 请求)=0;
    virtual boost::optional<Require> 取出请求()=0;
};


#endif //TRANSFER_请求队列池接口_H
