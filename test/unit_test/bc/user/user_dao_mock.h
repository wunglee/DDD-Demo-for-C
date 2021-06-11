#ifndef TRANSFER_UserDAOMock_H
#define TRANSFER_UserDAOMock_H
#include "../../../../src/bc/user/backend_adapters/user_dao_interface.h"
#include "../../../../src/bc/user/backend_adapters/user_po.h"
class UserDAOMock: public UserDAOInterface {
private:
    std::vector<UserPO> userPOs;
    static UserDAOMock * userDAOMock;
public:
    ~UserDAOMock() {
        UserDAOMock::userDAOMock = nullptr;
        userPOs.clear();
    }
    static UserDAOMock *BuildInstance() {
        if (userDAOMock == nullptr) {
            userDAOMock = new UserDAOMock();
        }
        return userDAOMock;
    }

    virtual boost::optional<UserPO> GetUserPO(std::string account_id) override{
        for (UserPO &user_po_:userPOs) {
            if (user_po_.account_id_ == account_id) {
                return user_po_;
            }
        }
        return boost::none;
    }
    virtual void AddUserPO(const UserPO user_po_) override{
        userPOs.push_back(user_po_);
    };
    virtual void UpdateUserPO(const UserPO _user_po) override{
        for (UserPO &user_po_:userPOs) {
            if (user_po_.account_id_ == _user_po.account_id_) {
                user_po_.frozen_=_user_po.frozen_;
            }
        }
    };
};


#endif //TRANSFER_UserDAOMock_H
