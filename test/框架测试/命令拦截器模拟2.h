#ifndef TRANSFER_命令拦截器模拟2_H
#define TRANSFER_命令拦截器模拟2_H
#include "../../src/框架组件/命令总线/命令拦截器.h"
class 命令拦截器模拟2: public 命令拦截器{
public:
    bool 执行前调用=false;
    bool 执行后调用=false;
    命令拦截器模拟2(std::string 名称):命令拦截器(名称){
    }
    virtual void 命令执行前处理(std::string 方法名,const boost::any 方法参数)override {
        执行前调用= true;
    };
    virtual void 命令执行后处理(std::string 方法名,const boost::any 方法参数,处理结果 &处理结果_)override{
        执行后调用= true;
    };
};
#endif //TRANSFER_命令拦截器模拟2_H
