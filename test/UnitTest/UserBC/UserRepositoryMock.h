#ifndef TRANSFER_用户仓储模拟_H
#define TRANSFER_用户仓储模拟_H
#include "../../../src/UserBC/Application/UserRepositoryInterface.h"
#include "../../../src/UserBC/Application/UserRepositoryInterface.h"
#include "../../../src/UserBC/Domain/User.h"

class UserRepositoryMock: public UserRepositoryInterface {
private:
    std::vector<User> & 用户集合_;
    UserRepositoryMock(std::vector<User> & 用户集合): 用户集合_(用户集合){}
    static UserRepositoryMock *用户仓储模拟_;
public:
    ~UserRepositoryMock() {
        UserRepositoryMock::用户仓储模拟_ = nullptr;
    }

    static UserRepositoryMock *构建单例(std::vector<User> & 用户集合) {
        if (用户仓储模拟_ == nullptr) {
            用户仓储模拟_ = new UserRepositoryMock(用户集合);
        }
        return 用户仓储模拟_;
    }
    static UserRepositoryMock *获取已存在的单例() {
        return 用户仓储模拟_;
    }
    virtual void 添加用户(std::string 账号) override{
        用户集合_.push_back(User(账号));
    };
    virtual void 更新用户(User &_用户) override{
        for(User& 用户_:用户集合_){
            if(用户_.获取账号()==_用户.获取账号()){
                _用户.是否冻结()?用户_.冻结():用户_.解冻();
            }
        }
    };
    virtual User 获取必须存在的用户(std::string 账号) override{
        for(User 用户_:用户集合_){
            if(用户_.获取账号()==账号){
                return 用户_;
            }
        }
        throw Exception((boost::format("没有找到用户:%1%") % 账号).str());
    }
};

#endif //TRANSFER_用户仓储模拟_H
