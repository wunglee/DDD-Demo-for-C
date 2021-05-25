#ifndef TRANSFER_请求_H
#define TRANSFER_请求_H
#include "boost/any.hpp"
#include "Response.h"
class Require {
private:
    std::string 请求ID;
    std::string 请求处理器名称;
    std::string 方法名;
    boost::any 参数;
    std::list <std::string> 过滤器配置;
    const std::function<void(Response& 处理结果_)> *回调方法_;
public:
    Require(const std::string 请求Id,
            const std::string 请求处理器名称,
            const std::string 方法名,
            const boost::any &参数,
            const std::function<void(Response &)> *回调方法,
            const std::list<std::string> &过滤器配置={}) :
       请求ID(请求Id),
       请求处理器名称(请求处理器名称),
       方法名(方法名),
       参数(参数),
       过滤器配置(过滤器配置),
       回调方法_(回调方法) {}

    const std::string 获取请求Id() const {
        return 请求ID;
    }

    const std::string 获取请求处理器名称() const {
        return 请求处理器名称;
    }

    const std::string 获取方法名() const {
        return 方法名;
    }

    const boost::any 获取参数() const {
        return 参数;
    }

    const std::list<std::string> 获取过滤器配置() const {
        return 过滤器配置;
    }

    const std::function<void(Response &)>* 获取回调方法() const {
        return 回调方法_;
    }
};
#endif //TRANSFER_请求_H
