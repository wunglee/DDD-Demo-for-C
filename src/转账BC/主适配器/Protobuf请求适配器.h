#ifndef TRANSFER_PROTOBUF请求适配器_H
#define TRANSFER_PROTOBUF请求适配器_H
#include "../../../src/框架组件/请求拦截/处理结果.h"
#include "../../../src/框架组件/请求拦截/请求.h"
#include "../../../src/框架组件/请求拦截/请求接收器.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "转账DTO.h"
//将请求转换为请求或事件后放入请求队列
class Protobuf请求适配器 {
private:
    请求接收器 * 请求接收器_= nullptr;
    static Protobuf请求适配器 * PB请求适配器_;
    Protobuf请求适配器(请求接收器 *请求接收器_) : 请求接收器_(请求接收器_) {}
    请求 构造请求(std::string 请求参数, std::function<void(处理结果&)>& 回调函数){
        申请转账DTO 申请转账DTO_("XX","YY",10);
        请求 请求_("1",
               "转账请求处理器",
               "申请转账",
               申请转账DTO_,
               回调函数);
        return 请求_;
    }
public:
    ~Protobuf请求适配器() {
        Protobuf请求适配器::PB请求适配器_= nullptr;
    }
    static Protobuf请求适配器* 构建单例(请求接收器 * 请求接收器_){
        if (PB请求适配器_ == nullptr) {
            PB请求适配器_ = new Protobuf请求适配器(请求接收器_);
        }
        return PB请求适配器_;
    }
    static Protobuf请求适配器* 获取单例(){
        if(Protobuf请求适配器::PB请求适配器_ == nullptr){
            throw "单例未创建";
        }
        return PB请求适配器_;
    }
    static void 销毁单例(){
        if(Protobuf请求适配器::PB请求适配器_ != nullptr){
            delete PB请求适配器_;
        }
    }
    int 请求请求(std::string 请求参数){
        int 单号;
        std::function<void(处理结果&)> 回调函数=[&](处理结果& 处理结果_) mutable{
            if(处理结果_.异常_==nullptr){
                单号=boost::any_cast<int>(处理结果_.返回值);
            }
        };
        请求 请求_=构造请求(请求参数, 回调函数);
        请求接收器_->提交请求(请求_);
        return 单号;
    }
};


#endif //TRANSFER_PROTOBUF请求适配器_H
