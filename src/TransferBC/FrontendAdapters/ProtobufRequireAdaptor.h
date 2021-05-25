#ifndef TRANSFER_PROTOBUF请求适配器_H
#define TRANSFER_PROTOBUF请求适配器_H
#include "../../../src/FrameworkComponents/LocalRequestionFilters/Response.h"
#include "../../../src/FrameworkComponents/LocalRequestionFilters/Require.h"
#include "../../../src/FrameworkComponents/LocalRequestionFilters/RequireAccepter.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "TransferDTO.h"
/**
 * 这是类其实可以是框架通过用户服务接口的服务描述自动生成的
 * 此处只是模拟，内部没有真实实现协议相关处理，并且
 * TODO:请求对象应该在其它线程异步处理，并异步回调当前上下文后返回客户端
 */
class ProtobufRequireAdaptor {
private:
    RequireAccepter * 请求接收器_= nullptr;
    static ProtobufRequireAdaptor * PB请求适配器_;
    ProtobufRequireAdaptor(RequireAccepter *请求接收器_) : 请求接收器_(请求接收器_) {}
    Require 构造请求(std::string 请求参数, std::function<void(Response&)>* 回调函数){
        申请转账DTO 申请转账DTO_("XX","YY",10);
        Require 请求_("1",
                    "TransferRequireMapping",
                    "申请转账",
                    申请转账DTO_,
                    回调函数);
        return 请求_;
    }
public:
    ~ProtobufRequireAdaptor() {
        ProtobufRequireAdaptor::PB请求适配器_= nullptr;
    }
    static ProtobufRequireAdaptor* 构建单例(RequireAccepter * 请求接收器_){
        if (PB请求适配器_ == nullptr) {
            PB请求适配器_ = new ProtobufRequireAdaptor(请求接收器_);
        }
        return PB请求适配器_;
    }
    static ProtobufRequireAdaptor* 获取单例(){
        if(ProtobufRequireAdaptor::PB请求适配器_ == nullptr){
            throw "单例未创建";
        }
        return PB请求适配器_;
    }
    static void 销毁单例(){
        if(ProtobufRequireAdaptor::PB请求适配器_ != nullptr){
            delete PB请求适配器_;
        }
    }
    int 请求请求(std::string 请求参数){
        int 单号;
        std::function<void(Response&)> 回调函数=[&](Response& 处理结果_) mutable{
            if(处理结果_.异常_==nullptr){
                单号=boost::any_cast<int>(处理结果_.返回值);
            }
        };
        Require 请求_=构造请求(请求参数, &回调函数);
        请求接收器_->提交请求(请求_);
        return 单号;
    }
};


#endif //TRANSFER_PROTOBUF请求适配器_H
