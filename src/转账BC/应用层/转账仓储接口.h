#ifndef TRANSFER_转账仓储接口_H
#define TRANSFER_转账仓储接口_H
#include "../领域层/转账.h"
#include "boost/optional.hpp"
class 转账仓储接口 {
public:
    virtual ~转账仓储接口(){}
    virtual void 新增转账(const 转账& 转账_)=0;
    virtual 转账 获取必须存在的转账(int 单号)=0;
    virtual void 更新转账状态(int 单号,转账::状态 状态)=0;
};
#endif //TRANSFER_转账仓储接口_H
