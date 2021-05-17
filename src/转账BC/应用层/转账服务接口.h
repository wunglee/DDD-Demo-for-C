#ifndef TRANSFER_转账服务接口_H
#define TRANSFER_转账服务接口_H
#include <string>
#include "boost/optional.hpp"
#include "../../框架组件/异常.h"
#include "../领域层/转账.h"
class 转账服务接口 {
public:
    virtual ~转账服务接口() {
    }
    virtual int 申请转账(std::string 付款账号, std::string 收款账号, float 金额)=0;
    virtual void 通知到账(int 单号,std::string 账号)=0;
    virtual void 通知取消(int 单号,异常 异常)=0;
    virtual void 通知申请退款(int 单号,异常 异常)=0;
    virtual void 通知出账(int 单号)=0;
    virtual boost::optional<转账> 获取转账(int 单号)=0;
};


#endif //TRANSFER_转账服务接口_H
