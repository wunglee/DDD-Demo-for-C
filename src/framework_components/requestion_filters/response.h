//
// Created by 王立 on 2021/5/16.
//

#ifndef TRANSFER_Response_H
#define TRANSFER_Response_H
#include <memory>
#include "boost/any.hpp"
#include "../exception.h"
class Response {
public:
    boost::any value;
    std::shared_ptr<Exception> exception= nullptr;
};

#endif //TRANSFER_Response_H
