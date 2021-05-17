#ifndef TRANSFER_用户查询服务接口_H
#define TRANSFER_用户查询服务接口_H
#include "boost/optional.hpp"
#include <string>
class 用户查询接口 {
public:
    virtual ~用户查询接口(){}
    virtual boost::optional<用户> 获取用户(std::string 账号) =0;
};


#endif //TRANSFER_用户查询服务接口_H
