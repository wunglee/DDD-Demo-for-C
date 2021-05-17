#ifndef TRANSFER_命令_H
#define TRANSFER_命令_H
#include "boost/any.hpp"
#include "处理结果.h"
class 命令 {
private:
    std::string 命令ID;
    std::string 命令处理器名称;
    std::string 方法名;
    boost::any 参数;
    std::list <std::string> 拦截器配置;
    std::function<void(处理结果& 处理结果_)> 回调方法;
public:
    命令(const std::string 命令Id,
       const std::string 命令处理器名称,
       const std::string 方法名,
       const boost::any &参数,
       const std::function<void(处理结果 &)> &回调方法,
       const std::list<std::string> &拦截器配置={}) :
       命令ID(命令Id),
       命令处理器名称(命令处理器名称),
       方法名(方法名),
       参数(参数),
       拦截器配置(拦截器配置),
       回调方法(回调方法) {}

    const std::string 获取命令Id() const {
        return 命令ID;
    }

    const std::string 获取命令处理器名称() const {
        return 命令处理器名称;
    }

    const std::string 获取方法名() const {
        return 方法名;
    }

    const boost::any 获取参数() const {
        return 参数;
    }

    const std::list<std::string> 获取拦截器配置() const {
        return 拦截器配置;
    }

    const std::function<void(处理结果 &)> 获取回调方法() const {
        return 回调方法;
    }
};
#endif //TRANSFER_命令_H
