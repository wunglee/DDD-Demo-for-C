#ifndef TRANSFER_请求处理器管理器_H
#define TRANSFER_请求处理器管理器_H
#include <map>
#include "请求处理器.h"
#include "请求队列池接口.h"
#include "../命名服务/命名服务管理器.h"
#include "请求拦截器.h"
#include "拦截器管理器.h"
#include "处理结果.h"
#include "../异常.h"
class 请求处理器管理器{
private:
    请求队列池接口* 请求队列池_= 命名服务管理器::获取单例()->查找服务<请求队列池接口 *>("请求队列池").value();
    std::map<std::string,请求处理器*> 请求处理器注册表;
    请求处理器管理器(const std::list<请求拦截器*> 拦截器链表=std::list<请求拦截器*>()) {
        拦截器管理器_=new 拦截器管理器(拦截器链表);
    }
    static 请求处理器管理器 * 请求处理器管理器_;
    拦截器管理器 *拦截器管理器_;
public:
    ~请求处理器管理器(){
        请求处理器注册表.clear();
        delete 拦截器管理器_;
        请求处理器管理器::请求处理器管理器_= nullptr;
    }
    static 请求处理器管理器* 构建单例(const std::list<请求拦截器*> 拦截器链表=std::list<请求拦截器*>()){
        if(请求处理器管理器::请求处理器管理器_== nullptr){
            请求处理器管理器::请求处理器管理器_=new 请求处理器管理器(拦截器链表);
        }
        return 请求处理器管理器::请求处理器管理器_;
    }
    static 请求处理器管理器* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(请求处理器管理器::请求处理器管理器_!= nullptr)
            delete 请求处理器管理器::请求处理器管理器_;
    }
    void 处理(){
        boost::optional<请求> 请求_Optional;
        while ((请求_Optional= 请求队列池_->取出请求()).has_value()){
            请求 请求_=请求_Optional.value();
            请求处理器* 请求处理器_=请求处理器注册表[请求_.获取请求处理器名称()];
            处理结果 处理结果_= 拦截器管理器_->拦截处理(*请求处理器_,
                                      请求_.获取方法名(),
                                      请求_.获取参数(),
                                      请求_.获取拦截器配置());
            if(请求_.获取回调方法()!= nullptr){
                请求_.获取回调方法()->operator()(处理结果_);
            }
        }
    }
    void 注册请求处理器(std::string 名称,请求处理器 *请求处理器){
        请求处理器注册表[名称]=请求处理器;
    }
    void 注销请求处理器(std::string 名称){
        请求处理器注册表.erase(名称);
    }
};


#endif //TRANSFER_请求处理器管理器_H
