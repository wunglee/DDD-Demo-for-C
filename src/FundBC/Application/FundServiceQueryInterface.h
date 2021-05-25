//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_资金帐户查询接口_H
#define TRANSFER_资金帐户查询接口_H
#include "boost/optional.hpp"
#include <string>
class FundServiceQueryInterface {
public:
    virtual ~FundServiceQueryInterface(){}
    virtual boost::optional<Fund> 获取资金帐户(std::string 账号)=0;
};


#endif //TRANSFER_资金帐户查询接口_H
