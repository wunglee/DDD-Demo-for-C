#ifndef TRANSFER_资金帐户仓储接口_H
#define TRANSFER_资金帐户仓储接口_H
#include "../Domain/Fund.h"
#include "boost/optional.hpp"
class FundRepositoryInterface {
public:
    virtual ~FundRepositoryInterface(){}
    virtual Fund 获取必须存在的资金帐户(std::string 账号)=0;
    virtual void 新增资金帐户(Fund& 资金帐户)=0;
    virtual void 更新资金帐户(Fund& 资金帐户)=0;
};
#endif //TRANSFER_资金帐户仓储接口_H
