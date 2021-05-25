#ifndef TRANSFER_用户查询服务接口_H
#define TRANSFER_用户查询服务接口_H
#include "boost/optional.hpp"
#include <string>
class UserQueryService {
public:
    virtual ~UserQueryService(){}
    virtual boost::optional<User> 获取用户(std::string 账号) =0;
};


#endif //TRANSFER_用户查询服务接口_H
