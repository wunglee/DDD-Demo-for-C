#ifndef TRANSFER_用户查询服务_H
#define TRANSFER_用户查询服务_H
#include "../Application/UserQueryService.h"

class UserQuery: public UserQueryService{
private:
    UserDAOInterface* 用户DAO接口_;
    UserQuery(UserDAOInterface * 用户DAO接口): 用户DAO接口_(用户DAO接口){}
    static UserQuery *用户查询_;
public:
    ~UserQuery() {
        UserQuery::用户查询_ = nullptr;
    }
    static UserQuery *构建单例(UserDAOInterface* 用户DAO接口_) {
        if (UserQuery::用户查询_ == nullptr) {
            UserQuery::用户查询_ = new UserQuery(用户DAO接口_);
        }
        return UserQuery::用户查询_;
    }
    static UserQuery *获取单例() {
        if(UserQuery::用户查询_ == nullptr){
            throw "单例未创建";
        }
        return UserQuery::用户查询_;
    }
    static void 销毁单例(){
        if(UserQuery::用户查询_ != nullptr)
          delete UserQuery::用户查询_;
    }
    virtual boost::optional<User> 获取用户(std::string 账号) override{
        boost::optional<UserPO> 用户PO_= 用户DAO接口_->获取用户PO(账号);
        if(用户PO_.has_value()){
            return User(用户PO_.value().账号_, 用户PO_.value().是否冻结_);
        }
        return boost::none;
    }
};


#endif //TRANSFER_用户查询服务_H
