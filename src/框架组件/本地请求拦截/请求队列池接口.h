//
// Created by 王立 on 2021/5/15.
//

#ifndef TRANSFER_请求队列池接口_H
#define TRANSFER_请求队列池接口_H
#include "请求.h"
#include "boost/optional.hpp"
class 请求队列池接口 {
public:
    virtual ~请求队列池接口(){}
    virtual void 加入请求(请求& 请求)=0;
    virtual boost::optional<请求> 取出请求()=0;
};


#endif //TRANSFER_请求队列池接口_H
