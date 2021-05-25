#ifndef TRANSFER_转账服务接口_H
#define TRANSFER_转账服务接口_H
#include <string>
#include "boost/optional.hpp"
#include "../../FrameworkComponents/Exception.h"
#include "../../TransferBC/Domain/Transfer.h"
class TransferServiceInterface {
public:
    virtual ~TransferServiceInterface() {
    }
    virtual int 申请转账(std::string 付款账号, std::string 收款账号, float 金额)=0;
    virtual void 通知到账(int 单号,std::string 账号)=0;
    virtual void 通知取消(int 单号, Exception 异常)=0;
    virtual void 通知申请退款(int 单号, Exception 异常)=0;
    virtual void 通知出账(int 单号)=0;
    virtual boost::optional<Transfer> 获取转账(int 单号)=0;
};


#endif //TRANSFER_转账服务接口_H
