#ifndef TRANSFER_资金帐户服务接口_H
#define TRANSFER_资金帐户服务接口_H
#include "../../FundBC/Domain/Fund.h"
#include <string>
#include <boost/any.hpp>
#include <boost/optional.hpp>
class FundServiceInterface {
public:
    virtual ~FundServiceInterface() {}
    virtual void 初始化资金(std::string 账号, float 金额)=0;
    virtual void 增加资金(int 单号,std::string 账号,float 金额)=0;
    virtual void 扣减资金(int 单号, std::string 账号, float 金额)=0;
    virtual void  设置禁止收款(std::string 账号, bool 是否禁止)=0;
    virtual void  设置禁止付款(std::string 账号, bool 是否禁止)=0;
    virtual void 添加资金帐户(std::string 账号)=0;
    virtual boost::optional<Fund> 获取资金帐户(std::string 账号)=0;
};


#endif //TRANSFER_资金帐户服务接口_H
