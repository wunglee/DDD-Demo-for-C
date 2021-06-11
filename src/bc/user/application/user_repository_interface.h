#ifndef TRANSFER_UserRepositoryInterface_H
#define TRANSFER_UserRepositoryInterface_H
#include "../domain/user.h"

class UserRepositoryInterface {
public:
    virtual ~UserRepositoryInterface(){};
    virtual void AddUser(std::string account_id) =0;
    virtual void UpdateUser(User &user) =0;
    virtual User GetExistedUser(std::string account_id)=0;
};
#endif //TRANSFER_UserRepositoryInterface_H
