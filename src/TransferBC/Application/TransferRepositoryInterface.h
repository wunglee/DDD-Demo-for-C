#ifndef TRANSFER_转账仓储接口_H
#define TRANSFER_转账仓储接口_H
#include "../Domain/Transfer.h"
#include "boost/optional.hpp"
class TransferRepositoryInterface {
public:
    virtual ~TransferRepositoryInterface(){}
    virtual void 新增转账(const Transfer& 转账_)=0;
    virtual Transfer 获取必须存在的转账(int 单号)=0;
    virtual void 更新转账状态(int 单号, Transfer::状态 状态)=0;
};
#endif //TRANSFER_转账仓储接口_H
