#ifndef TRANSFER_请求过滤器模拟2_H
#define TRANSFER_请求过滤器模拟2_H
#include "../../src/FrameworkComponents/RequestionFilters/Filter.h"
class 请求过滤器模拟2: public Filter{
public:
    bool 执行前调用=false;
    bool 执行后调用=false;
    请求过滤器模拟2(std::string 名称): Filter(名称){
    }
    virtual void 请求执行前处理(std::string 方法名,const boost::any 方法参数)override {
        执行前调用= true;
    };
    virtual void 请求执行后处理(std::string 方法名, const boost::any 方法参数, Response &处理结果_)override{
        执行后调用= true;
    };
};
#endif //TRANSFER_请求过滤器模拟2_H
