#ifndef TRANSFER_用户查询模拟_H
#define TRANSFER_用户查询模拟_H
#include "../../../src/UserBC/Domain/User.h"
#include "../../../src/UserBC/Application/UserQueryService.h"
class UserQueryMock: public UserQueryService{
private:
    std::vector<User> & 用户集合_;
    UserQueryMock(std::vector<User> & 用户集合): 用户集合_(用户集合){}
    static UserQueryMock *用户查询模拟_;
public:
    ~UserQueryMock() {
        UserQueryMock::用户查询模拟_ = nullptr;
    }
    static UserQueryMock *构建单例(std::vector<User> & 用户集合_) {
        if (用户查询模拟_ == nullptr) {
            用户查询模拟_ = new UserQueryMock(用户集合_);
        }
        return 用户查询模拟_;
    }
    virtual boost::optional<User> 获取用户(std::string 账号) override{
        for(User& 用户_:用户集合_){
            if(用户_.获取账号()==账号){
                return User(用户_.获取账号(),
                            用户_.是否冻结());
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_用户查询模拟_H
