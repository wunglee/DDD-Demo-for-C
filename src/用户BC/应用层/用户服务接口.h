#ifndef TRANSFER_用户服务接口_H
#define TRANSFER_用户服务接口_H

#include <boost/optional.hpp>
#include "../领域层/用户.h"

class 用户服务接口 {
public:
    virtual ~用户服务接口() {
    }
    virtual void 添加用户(std::string 账号)=0;
    virtual void 冻结用户(std::string 账号)=0;
    virtual void 解冻用户(std::string 账号)=0;
    virtual bool 是否已冻结(std::string 账号)=0;
    virtual boost::optional<用户> 获取用户(std::string 账号) =0;
};


#endif //TRANSFER_用户服务接口_H
