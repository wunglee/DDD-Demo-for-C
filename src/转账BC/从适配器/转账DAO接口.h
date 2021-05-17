#ifndef TRANSFER_转账DAO接口_H
#define TRANSFER_转账DAO接口_H
#include "boost/optional.hpp"
#include "转账PO.h"
class 转账DAO接口 {
public:
    virtual ~转账DAO接口(){}
    virtual void 新增转账PO(const 转账PO &转账PO)=0;
    virtual boost::optional<转账PO> 获取转账PO(int 单号)=0;
    virtual void 更新转账PO状态(int 单号,int 状态)=0;
};


#endif //TRANSFER_转账DAO接口_H
