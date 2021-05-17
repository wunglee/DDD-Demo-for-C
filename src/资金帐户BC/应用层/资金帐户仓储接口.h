#ifndef TRANSFER_资金帐户仓储接口_H
#define TRANSFER_资金帐户仓储接口_H
#include "../领域层/资金帐户.h"
#include "boost/optional.hpp"
class 资金帐户仓储接口 {
public:
    virtual ~资金帐户仓储接口(){}
    virtual void 新增资金帐户(资金帐户& 资金帐户)=0;
    virtual void 更新资金帐户(资金帐户& 资金帐户)=0;
};
#endif //TRANSFER_资金帐户仓储接口_H
