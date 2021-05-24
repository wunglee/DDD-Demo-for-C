#ifndef TRANSFER_请求拦截器_H
#define TRANSFER_请求拦截器_H

class 请求拦截器{
public:
    const std::string 名称_;
    请求拦截器(const std::string 名称) : 名称_(名称) {}
    virtual void 请求执行前处理(std::string 方法名,const boost::any 方法参数)=0;
    virtual void 请求执行后处理(std::string 方法名,const boost::any 方法参数,处理结果 &处理结果_)=0;
};
#endif //TRANSFER_请求拦截器_H
