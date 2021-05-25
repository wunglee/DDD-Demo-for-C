//
// Created by 王立 on 2021/5/16.
//

#ifndef TRANSFER_处理结果_H
#define TRANSFER_处理结果_H
#include "boost/any.hpp"
#include "../Exception.h"
class Response {
public:
    boost::any 返回值;
    std::shared_ptr<Exception> 异常_= nullptr;
};

#endif //TRANSFER_处理结果_H
