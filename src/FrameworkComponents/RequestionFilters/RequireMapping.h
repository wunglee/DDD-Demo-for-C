#ifndef TRANSFER_请求处理器_H
#define TRANSFER_请求处理器_H
#include "Response.h"
#include "boost/any.hpp"
class RequireMapping {
public:
    virtual ~RequireMapping(){
    }
    virtual Response 处理(std::string 方法名, const boost::any &方法参数)=0;
};

#endif //TRANSFER_请求处理器_H
