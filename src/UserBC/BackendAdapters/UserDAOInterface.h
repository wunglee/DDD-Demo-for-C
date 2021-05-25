#ifndef TRANSFER_用户DAO接口_H
#define TRANSFER_用户DAO接口_H
#include "boost/optional.hpp"
#include "UserPO.h"

class UserDAOInterface {
public:
    virtual ~UserDAOInterface(){}
    virtual boost::optional<UserPO> 获取用户PO(std::string 账号) =0;
    virtual void 添加用户PO(const UserPO 用户PO) =0;
    virtual void 更新用户PO(const UserPO 用户PO) =0;
};
#endif //TRANSFER_用户DAO接口_H
