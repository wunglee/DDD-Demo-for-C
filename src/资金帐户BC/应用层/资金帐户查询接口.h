//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_资金帐户查询接口_H
#define TRANSFER_资金帐户查询接口_H
#include "boost/optional.hpp"
#include <string>
class 资金帐户查询接口 {
public:
    virtual ~资金帐户查询接口(){}
    virtual boost::optional<资金帐户> 获取资金帐户(std::string 账号)=0;
};


#endif //TRANSFER_资金帐户查询接口_H
