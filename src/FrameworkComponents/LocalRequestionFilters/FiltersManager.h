#ifndef TRANSFER_拦截器管理器_H
#define TRANSFER_拦截器管理器_H
#include <list>
#include <stack>
#include "boost/any.hpp"
#include "Filter.h"
#include "Response.h"
#include "RequireMapping.h"
class 拦截器管理器 {
private:
    std::list<Filter*> 拦截器链表;
    void 前置拦截(std::string 方法名,const boost::any &参数,const std::list<std::string> &拦截器配置, std::stack<Filter*> &调用栈) {
        for(Filter* 请求拦截器_:拦截器链表){
            if(需要拦截(请求拦截器_->名称_, 拦截器配置)){
                请求拦截器_->请求执行前处理(方法名,参数);
                调用栈.push(请求拦截器_);
            }
        }
    };
    Response &后置拦截(std::string 方法名, const boost::any &参数, Response &处理结果_, std::stack<Filter*> &调用栈) const {
        while(!调用栈.empty()){
            调用栈.top()->请求执行后处理(方法名,参数,处理结果_);
            调用栈.pop();
        }
        return 处理结果_;
    }
    bool 需要拦截(std::string 拦截器名称,const std::list <std::string> &拦截器配置){
        for(std::string 配置拦截器:拦截器配置){
            if(配置拦截器==拦截器名称){
                return true;
            }
        }
        return false;
    }
public:
    拦截器管理器(const std::list <Filter*> &拦截器链表) : 拦截器链表(拦截器链表) {}
    Response 拦截处理(RequireMapping &请求处理器_, std::string 方法名, const boost::any &参数, const std::list <std::string> &拦截器配置){
        try{
            Response 处理结果_;
            std::stack<Filter*> 调用栈;
            前置拦截(方法名, 参数, 拦截器配置, 调用栈);
            处理结果_=请求处理器_.处理(方法名,参数);
            return 后置拦截(方法名, 参数, 处理结果_, 调用栈);
        }catch(Exception _异常){
            Response 处理结果_;
            处理结果_.返回值=boost::none;
            处理结果_.异常_=std::make_shared<Exception>(_异常);
            return 处理结果_;
        }
    }
};


#endif //TRANSFER_拦截器管理器_H
