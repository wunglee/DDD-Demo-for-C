#ifndef TRANSFER_请求过滤器_H
#define TRANSFER_请求过滤器_H

class Filter{
public:
    const std::string 名称_;
    Filter(const std::string 名称) : 名称_(名称) {}
    virtual void 请求执行前处理(std::string 方法名,const boost::any 方法参数)=0;
    virtual void 请求执行后处理(std::string 方法名, const boost::any 方法参数, Response &处理结果_)=0;
};
#endif //TRANSFER_请求过滤器_H
