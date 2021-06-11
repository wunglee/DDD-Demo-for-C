#ifndef TRANSFER_UserDAOInterface_H
#define TRANSFER_UserDAOInterface_H
#include "boost/optional.hpp"
#include "user_po.h"

class UserDAOInterface {
public:
    virtual ~UserDAOInterface(){}
    virtual boost::optional<UserPO> GetUserPO(std::string account_id) =0;
    virtual void AddUserPO(const UserPO userPO) =0;
    virtual void UpdateUserPO(const UserPO userPO) =0;
};
#endif //TRANSFER_UserDAOInterface_H
