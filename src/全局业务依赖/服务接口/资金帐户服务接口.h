#ifndef TRANSFER_资金帐户服务接口_H
#define TRANSFER_资金帐户服务接口_H
#include "../../资金帐户BC/领域层/资金帐户.h"
#include <string>
#include <boost/any.hpp>
#include <boost/optional.hpp>
class 资金帐户服务接口 {
public:
    virtual ~资金帐户服务接口() {}
    virtual void 初始化资金(std::string 账号, float 金额)=0;
    virtual void 增加资金(int 单号,std::string 账号,float 金额)=0;
    virtual void 扣减资金(int 单号, std::string 账号, float 金额)=0;
    virtual void  设置禁止收款(std::string 账号, bool 是否禁止)=0;
    virtual void  设置禁止付款(std::string 账号, bool 是否禁止)=0;
    virtual void 添加资金帐户(std::string 账号)=0;
    virtual boost::optional<资金帐户> 获取资金帐户(std::string 账号)=0;
};


#endif //TRANSFER_资金帐户服务接口_H
