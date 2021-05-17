#ifndef TRANSFER_用户DAO接口_H
#define TRANSFER_用户DAO接口_H
#include "boost/optional.hpp"
#include "用户PO.h"

class 用户DAO接口 {
public:
    virtual ~用户DAO接口(){}
    virtual boost::optional<用户PO> 获取用户PO(std::string 账号) =0;
    virtual void 添加用户PO(const 用户PO 用户PO) =0;
    virtual void 更新用户PO(const 用户PO 用户PO) =0;
};
#endif //TRANSFER_用户DAO接口_H
