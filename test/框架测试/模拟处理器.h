#ifndef TRANSFER_模拟处理器_H
#define TRANSFER_模拟处理器_H
#include "../../src/框架组件/请求拦截/请求处理器.h"
#include "../../src/框架组件/请求拦截/处理结果.h"
#include <boost/any.hpp>

class 模拟处理器:public 请求处理器{
public:
    virtual 处理结果 处理(std::string 方法名,const boost::any &方法参数) override {
         处理结果 处理结果_;
         处理结果_.返回值=true;
         return 处理结果_;
    }
};
#endif //TRANSFER_模拟处理器_H
