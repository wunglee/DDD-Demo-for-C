#ifndef TRANSFER_用户服务模拟_H
#define TRANSFER_用户服务模拟_H
#include "../../../src/GlobalBusinessDependency/ServiceInterfaces/UserServiceInterface.h"

class UserServiceMock: public UserServiceInterface{
private:
    std::map<std::string,bool> 冻结状态集合_;
    static UserServiceMock* 用户服务模拟_;
public:
    ~UserServiceMock() {
        UserServiceMock::用户服务模拟_= nullptr;
        冻结状态集合_.clear();
    }
    static UserServiceMock* 构造单例(){
        if (用户服务模拟_ == nullptr) {
            用户服务模拟_ = new UserServiceMock();
        }
        return 用户服务模拟_;
    }
    static void 销毁单例(){
        if (用户服务模拟_ != nullptr) {
            delete 用户服务模拟_;
        }
    }
    static UserServiceMock* 获取单例(){
        return 构造单例();
    }
    virtual void 添加用户(std::string 账号) override {
        if(冻结状态集合_.find(账号) == 冻结状态集合_.end())
            冻结状态集合_[账号]=false;
    };
    virtual void 冻结用户(std::string 账号) override{
        if(冻结状态集合_.find(账号) != 冻结状态集合_.end())
            冻结状态集合_[账号]=true;
    };
    virtual void 解冻用户(std::string 账号) override{
        if(冻结状态集合_.find(账号) != 冻结状态集合_.end())
            冻结状态集合_[账号]=false;
    };
    virtual bool 是否已冻结(std::string 账号) override{
        return 冻结状态集合_[账号];
    };
    virtual boost::optional<User> 获取用户(std::string 账号) override{
        return User(账号, 冻结状态集合_[账号]);
    };
};


#endif //TRANSFER_用户服务模拟_H
