#ifndef TRANSFER_转账前端控制器_H
#define TRANSFER_转账前端控制器_H
#include "../../../src/框架组件/请求拦截/请求处理器.h"
#include "../../../src/框架组件/请求拦截/处理结果.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "../../全局业务依赖/服务接口/转账服务接口.h"
#include "boost/any.hpp"
#include "转账DTO.h"
class 转账请求处理器 :public 请求处理器{
private:
    转账服务接口 * 转账服务接口_;
    static 转账请求处理器* 转账请求处理器_;
    转账请求处理器(转账服务接口 *转账服务接口_) : 转账服务接口_(转账服务接口_) {}
public:
    virtual ~转账请求处理器(){
    }
    static 转账请求处理器* 构建单例(转账服务接口 * 转账服务接口){
        if (转账请求处理器::转账请求处理器_ == nullptr) {
            转账请求处理器::转账请求处理器_ = new 转账请求处理器(转账服务接口);
        }
        return 转账请求处理器::转账请求处理器_;
    }
    static 转账请求处理器* 获取单例(){
        if (转账请求处理器::转账请求处理器_ == nullptr) {
            throw "单例未构建";
        }
        return 转账请求处理器::转账请求处理器_;
    }
    static void 销毁单例(){
        if(转账请求处理器::转账请求处理器_!= nullptr){
            delete 转账请求处理器::转账请求处理器_;
        }
    }
    virtual 处理结果 处理(std::string 方法名,const boost::any &方法参数) override {
        申请转账DTO 申请转账DTO_=boost::any_cast<申请转账DTO>(方法参数);
        处理结果 处理结果_;
        if(方法名=="申请转账") {
           int 单号 = 转账服务接口_->申请转账(申请转账DTO_.付款账号,
                                  申请转账DTO_.收款账号,
                                  申请转账DTO_.金额);
           处理结果_.返回值=单号;
        }
        return 处理结果_;
    }
};


#endif //TRANSFER_转账前端控制器_H
