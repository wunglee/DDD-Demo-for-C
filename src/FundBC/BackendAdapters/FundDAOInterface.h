//
// Created by 王立 on 2021/5/12.
//

#ifndef TRANSFER_资金帐户DAO接口_H
#define TRANSFER_资金帐户DAO接口_H
#include "FundPO.h"

class FundDAOInterface {
public:
    virtual ~FundDAOInterface(){}
    virtual void 新增资金帐户PO(const FundPO& 资金帐户PO)=0;
    virtual void 更新资金帐户PO(const FundPO& 资金帐户PO)=0;
    virtual boost::optional<FundPO>  获取资金帐户PO(const std::string 账号)=0;
};


#endif //TRANSFER_资金帐户DAO接口_H
