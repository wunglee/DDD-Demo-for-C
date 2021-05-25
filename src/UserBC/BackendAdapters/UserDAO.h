#ifndef TRANSFER_用户DAO_H
#define TRANSFER_用户DAO_H
#include "UserDAOInterface.h"
#include "UserPO.h"
class UserDAO : public UserDAOInterface {
private:
    std::vector<UserPO> 用户PO集合_;
    static UserDAO * 单例_;
public:
    ~UserDAO() {
        用户PO集合_.clear();
        UserDAO::单例_= nullptr;
    }
    static UserDAO * 构建单例() {
        if (UserDAO::单例_ == nullptr) {
            UserDAO::单例_ = new UserDAO();
        }
        return UserDAO::单例_;
    }
    static UserDAO * 获取单例() {
        return 构建单例();
    }
    static void 销毁单例() {
        if(UserDAO::单例_ != nullptr)
           delete UserDAO::单例_;
    }
    virtual boost::optional<UserPO> 获取用户PO(std::string 账号) override{
        for (UserPO &用户PO_:用户PO集合_) {
            if (用户PO_.账号_ == 账号) {
                return 用户PO_;
            }
        }
        return boost::none;
    }
    virtual void 添加用户PO(const UserPO 用户PO_) override{
        用户PO集合_.push_back(用户PO_);
    };
    virtual void 更新用户PO(const UserPO _用户PO) override{
        for (UserPO &用户PO_:用户PO集合_) {
            if (用户PO_.账号_ == _用户PO.账号_) {
                 用户PO_.是否冻结_=_用户PO.是否冻结_;
            }
        }
    };
};
#endif //TRANSFER_用户DAO_H
