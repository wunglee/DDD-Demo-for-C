#ifndef TRANSFER_拦截器管理器_H
#define TRANSFER_拦截器管理器_H
#include <list>
#include <stack>
#include "boost/any.hpp"
#include "命令拦截器.h"
#include "处理结果.h"
#include "命令处理器.h"
class 拦截器管理器 {
private:
    std::list<命令拦截器*> 拦截器链表;
    void 前置拦截(std::string 方法名,const boost::any &参数,const std::list<std::string> &拦截器配置, std::stack<命令拦截器*> &调用栈) {
        for(命令拦截器* 命令拦截器_:拦截器链表){
            if(需要拦截(命令拦截器_->名称_, 拦截器配置)){
                命令拦截器_->命令执行前处理(方法名,参数);
                调用栈.push(命令拦截器_);
            }
        }
    };
    处理结果 &后置拦截(std::string 方法名, const boost::any &参数,处理结果 &处理结果_, std::stack<命令拦截器*> &调用栈) const {
        while(!调用栈.empty()){
            调用栈.top()->命令执行后处理(方法名,参数,处理结果_);
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
    拦截器管理器(const std::list <命令拦截器*> &拦截器链表) : 拦截器链表(拦截器链表) {}
    处理结果 拦截处理(命令处理器 &命令处理器_,std::string 方法名,const boost::any &参数,const std::list <std::string> &拦截器配置){
        处理结果 处理结果_;
        try{
            std::stack<命令拦截器*> 调用栈;
            前置拦截(方法名, 参数, 拦截器配置, 调用栈);
            处理结果_=命令处理器_.处理(方法名,参数);
            处理结果_ = 后置拦截(方法名, 参数, 处理结果_, 调用栈);
        }catch(异常 _异常){
            处理结果_=处理结果();
            处理结果_.返回值=boost::none;
            处理结果_.异常_=std::make_shared<异常>(_异常);
        }
        return 处理结果_;
    }
};


#endif //TRANSFER_拦截器管理器_H
