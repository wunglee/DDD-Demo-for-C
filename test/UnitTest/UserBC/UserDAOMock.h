#ifndef TRANSFER_用户DAO模拟_H
#define TRANSFER_用户DAO模拟_H
#include "../../../src/UserBC/BackendAdapters/UserDAOInterface.h"
#include "../../../src/UserBC/BackendAdapters/UserPO.h"
class UserDAOMock: public UserDAOInterface {
private:
    std::vector<UserPO> 用户PO集合_;
    static UserDAOMock * 用户DAO模拟_;
public:
    ~UserDAOMock() {
        UserDAOMock::用户DAO模拟_ = nullptr;
        用户PO集合_.clear();
    }
    static UserDAOMock *构建单例() {
        if (用户DAO模拟_ == nullptr) {
            用户DAO模拟_ = new UserDAOMock();
        }
        return 用户DAO模拟_;
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


#endif //TRANSFER_用户DAO模拟_H
