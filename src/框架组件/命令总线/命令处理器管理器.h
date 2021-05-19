#ifndef TRANSFER_命令处理器管理器_H
#define TRANSFER_命令处理器管理器_H
#include <map>
#include "命令处理器.h"
#include "命令队列池接口.h"
#include "../命名服务/命名服务管理器.h"
#include "命令拦截器.h"
#include "拦截器管理器.h"
#include "处理结果.h"
#include "../异常.h"
class 命令处理器管理器{
private:
    命令队列池接口* 命令队列池_= 命名服务管理器::获取单例()->查找服务<命令队列池接口 *>("命令队列池").value();
    std::map<std::string,命令处理器*> 命令处理器注册表;
    命令处理器管理器(const std::list<命令拦截器*> 拦截器链表=std::list<命令拦截器*>()) {
        拦截器管理器_=new 拦截器管理器(拦截器链表);
    }
    static 命令处理器管理器 * 命令处理器管理器_;
    拦截器管理器 *拦截器管理器_;
public:
    ~命令处理器管理器(){
        命令处理器注册表.clear();
        delete 拦截器管理器_;
        命令处理器管理器::命令处理器管理器_= nullptr;
    }
    static 命令处理器管理器* 构建单例(const std::list<命令拦截器*> 拦截器链表=std::list<命令拦截器*>()){
        if(命令处理器管理器::命令处理器管理器_== nullptr){
            命令处理器管理器::命令处理器管理器_=new 命令处理器管理器(拦截器链表);
        }
        return 命令处理器管理器::命令处理器管理器_;
    }
    static 命令处理器管理器* 获取单例(){
        if(命令处理器管理器::命令处理器管理器_== nullptr){
            throw "单例还未创建";
        }
        return 命令处理器管理器::命令处理器管理器_;
    }
    static void 销毁单例(){
        if(命令处理器管理器::命令处理器管理器_!= nullptr)
            delete 命令处理器管理器::命令处理器管理器_;
    }
    void 处理(){
        boost::optional<命令> 命令_Optional;
        while ((命令_Optional= 命令队列池_->取出命令()).has_value()){
            命令 命令_=命令_Optional.value();
            命令处理器* 命令处理器_=命令处理器注册表[命令_.获取命令处理器名称()];
            处理结果 处理结果_= 拦截器管理器_->拦截处理(*命令处理器_,
                                      命令_.获取方法名(),
                                      命令_.获取参数(),
                                      命令_.获取拦截器配置());
            命令_.获取回调方法().operator()(处理结果_);
        }
    }
    void 注册命令处理器(std::string 名称,命令处理器 *命令处理器){
        命令处理器注册表[名称]=命令处理器;
    }
    void 注销命令处理器(std::string 名称){
        命令处理器注册表.erase(名称);
    }
};


#endif //TRANSFER_命令处理器管理器_H
