#ifndef TRANSFER_用户仓储接口_H
#define TRANSFER_用户仓储接口_H
#include "../领域层/用户.h"

class 用户仓储接口 {
public:
    virtual ~用户仓储接口(){};
    virtual void 添加用户(std::string 账号) =0;
    virtual void 更新用户(用户 &用户_) =0;
    virtual 用户 获取必须存在的用户(std::string 账号)=0;
};
#endif //TRANSFER_用户仓储接口_H
