#ifndef TRANSFER_转账前端控制器_H
#define TRANSFER_转账前端控制器_H
#include "../../../src/框架组件/本地请求拦截/请求处理器.h"
#include "../../../src/框架组件/本地请求拦截/处理结果.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "../../../src/全局业务依赖/服务接口/用户服务接口.h"
#include "boost/any.hpp"
#include "用户DTO.h"
class 用户请求处理器 :public 请求处理器{
private:
    用户服务接口 * 用户服务接口_;
    static 用户请求处理器* 用户请求处理器_;
    用户请求处理器(用户服务接口 *用户服务接口_) : 用户服务接口_(用户服务接口_) {}
public:
    virtual ~用户请求处理器(){
        用户请求处理器::用户请求处理器_= nullptr;
    }
    static 用户请求处理器* 构建单例(用户服务接口 * 用户服务接口){
        if (用户请求处理器::用户请求处理器_ == nullptr) {
            用户请求处理器::用户请求处理器_ = new 用户请求处理器(用户服务接口);
        }
        return 用户请求处理器::用户请求处理器_;
    }
    static 用户请求处理器* 获取单例(){
        if (用户请求处理器::用户请求处理器_ == nullptr) {
            throw "单例未构建";
        }
        return 用户请求处理器::用户请求处理器_;
    }
    static void 销毁单例(){
        if(用户请求处理器::用户请求处理器_!= nullptr){
            delete 用户请求处理器::用户请求处理器_;
        }
    }
    virtual 处理结果 处理(std::string 方法名,const boost::any &方法参数) override {
        处理结果 处理结果_;
        if(方法名=="创建用户") {
            用户DTO 用户DTO_=boost::any_cast<用户DTO>(方法参数);
            用户服务接口_->添加用户(用户DTO_.用户名);
        }
        if(方法名=="冻结用户") {
            用户DTO 用户DTO_=boost::any_cast<用户DTO>(方法参数);
            用户服务接口_->冻结用户(用户DTO_.用户名);
        }
        if(方法名=="解冻用户") {
            用户DTO 用户DTO_=boost::any_cast<用户DTO>(方法参数);
            用户服务接口_->解冻用户(用户DTO_.用户名);
        }
        if(方法名=="获取用户") {
            用户DTO 用户DTO_=boost::any_cast<用户DTO>(方法参数);
            boost::optional<用户>  用户_ = 用户服务接口_->获取用户(用户DTO_.用户名);
            if(用户_.has_value()){
                处理结果_.返回值=用户_.value();
            }else{
                处理结果_.异常_=std::make_shared<异常>("未查到该用户");
            }
        }
        if(方法名=="是否已冻结") {
            用户DTO 用户DTO_=boost::any_cast<用户DTO>(方法参数);
            bool 冻结_ = 用户服务接口_->是否已冻结(用户DTO_.用户名);
            处理结果_.返回值=冻结_;
        }
        return 处理结果_;
    }
};


#endif //TRANSFER_转账前端控制器_H
