#ifndef TRANSFER_转账前端控制器_H
#define TRANSFER_转账前端控制器_H
#include "../../../src/FrameworkComponents/RequestionFilters/RequireMapping.h"
#include "../../../src/FrameworkComponents/RequestionFilters/Response.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../GlobalBusinessDependency/ServiceInterfaces/TransferServiceInterface.h"
#include "boost/any.hpp"
#include "TransferDTO.h"
class TransferRequireMapping : public RequireMapping{
private:
    TransferServiceInterface * 转账服务接口_;
    static TransferRequireMapping* 转账请求处理器_;
    TransferRequireMapping(TransferServiceInterface *转账服务接口_) : 转账服务接口_(转账服务接口_) {}
public:
    virtual ~TransferRequireMapping(){
    }
    static TransferRequireMapping* 构建单例(TransferServiceInterface * 转账服务接口){
        if (TransferRequireMapping::转账请求处理器_ == nullptr) {
            TransferRequireMapping::转账请求处理器_ = new TransferRequireMapping(转账服务接口);
        }
        return TransferRequireMapping::转账请求处理器_;
    }
    static TransferRequireMapping* 获取单例(){
        if (TransferRequireMapping::转账请求处理器_ == nullptr) {
            throw "单例未构建";
        }
        return TransferRequireMapping::转账请求处理器_;
    }
    static void 销毁单例(){
        if(TransferRequireMapping::转账请求处理器_ != nullptr){
            delete TransferRequireMapping::转账请求处理器_;
        }
    }
    virtual Response 处理(std::string 方法名, const boost::any &方法参数) override {
        申请转账DTO 申请转账DTO_=boost::any_cast<申请转账DTO>(方法参数);
        Response 处理结果_;
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
