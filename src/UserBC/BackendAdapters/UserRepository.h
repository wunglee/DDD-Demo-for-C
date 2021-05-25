#ifndef TRANSFER_用户仓储_H
#define TRANSFER_用户仓储_H
#include "../Application/UserRepositoryInterface.h"
#include "UserPO.h"
#include "../Domain/User.h"
#include "UserDAOInterface.h"

class UserRepository : public UserRepositoryInterface {
private:
    UserDAOInterface* 用户DAO接口_;
    UserRepository(UserDAOInterface * 用户DAO接口): 用户DAO接口_(用户DAO接口){}
    static UserRepository *用户仓储_;
public:
    ~UserRepository() {
        UserRepository::用户仓储_ = nullptr;
    }

    static UserRepository *构建单例(UserDAOInterface* 用户DAO接口_) {
        if (UserRepository::用户仓储_ == nullptr) {
            UserRepository::用户仓储_ = new UserRepository(用户DAO接口_);
        }
        return UserRepository::用户仓储_;
    }
    static UserRepository *获取单例() {
        if(UserRepository::用户仓储_ == nullptr){
            throw "单例未创建";
        }
        return UserRepository::用户仓储_;
    }
    static void 销毁单例() {
        if(UserRepository::用户仓储_ != nullptr)
           delete UserRepository::用户仓储_;
    }
    virtual void 添加用户(std::string 账号) override{
        用户DAO接口_->添加用户PO(UserPO(账号));
    };
    virtual void 更新用户(User &用户_) override{
        用户DAO接口_->更新用户PO(UserPO(用户_.获取账号(), 用户_.是否冻结()));
    };
    virtual User 获取必须存在的用户(std::string 账号) override{
        boost::optional<UserPO> 用户PO_= 用户DAO接口_->获取用户PO(账号);
        if(用户PO_.has_value()){
            return User(用户PO_.value().账号_, 用户PO_.value().是否冻结_);
        }
        throw Exception((boost::format("没有找到用户:%1%") % 账号).str());
    }
};
#endif //TRANSFER_用户仓储_H
