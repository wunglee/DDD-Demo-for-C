#ifndef TRANSFER_UserQuery_H
#define TRANSFER_UserQuery_H
#include "../application/user_query_service.h"

class UserQuery: public UserQueryService{
private:
    UserDAOInterface* userDAOInterface_;
    UserQuery(UserDAOInterface * userDAOInterface): userDAOInterface_(userDAOInterface){}
    static UserQuery *userQuery_;
public:
    ~UserQuery() {
        UserQuery::userQuery_ = nullptr;
    }
    static UserQuery *BuildInstance(UserDAOInterface* userDAOInterface_) {
        if (UserQuery::userQuery_ == nullptr) {
            UserQuery::userQuery_ = new UserQuery(userDAOInterface_);
        }
        return UserQuery::userQuery_;
    }
    static UserQuery *GetInstance() {
        if(UserQuery::userQuery_ == nullptr){
            throw "单例未创建";
        }
        return UserQuery::userQuery_;
    }
    static void DestroyInstance(){
        if(UserQuery::userQuery_ != nullptr)
          delete UserQuery::userQuery_;
    }
    virtual boost::optional<User> GetUser(std::string account_id) override{
        boost::optional<UserPO> userPo_optional= userDAOInterface_->GetUserPO(account_id);
        if(userPo_optional.has_value()){
            return User(userPo_optional.value().account_id_, userPo_optional.value().frozen_);
        }
        return boost::none;
    }
};


#endif //TRANSFER_UserQuery_H
