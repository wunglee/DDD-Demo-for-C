#ifndef TRANSFER_UserQueryMock_H
#define TRANSFER_UserQueryMock_H
#include "../../../../src/bc/user/domain/user.h"
#include "../../../../src/bc/user/application/user_query_service.h"
class UserQueryMock: public UserQueryService{
private:
    std::vector<User> & users_;
    UserQueryMock(std::vector<User> & users): users_(users){}
    static UserQueryMock *userQueryMock;
public:
    ~UserQueryMock() {
        UserQueryMock::userQueryMock = nullptr;
    }
    static UserQueryMock *BuildInstance(std::vector<User> & users) {
        if (userQueryMock == nullptr) {
            userQueryMock = new UserQueryMock(users);
        }
        return userQueryMock;
    }
    virtual boost::optional<User> GetUser(std::string account_id) override{
        for(User& user_:users_){
            if(user_.GetAccountId() == account_id){
                return User(user_.GetAccountId(),
                            user_.isFrozen());
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_UserQueryMock_H
