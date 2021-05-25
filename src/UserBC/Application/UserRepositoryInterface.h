#ifndef TRANSFER_用户仓储接口_H
#define TRANSFER_用户仓储接口_H
#include "../Domain/User.h"

class UserRepositoryInterface {
public:
    virtual ~UserRepositoryInterface(){};
    virtual void 添加用户(std::string 账号) =0;
    virtual void 更新用户(User &用户_) =0;
    virtual User 获取必须存在的用户(std::string 账号)=0;
};
#endif //TRANSFER_用户仓储接口_H
