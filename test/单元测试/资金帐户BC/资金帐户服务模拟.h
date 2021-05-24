#ifndef TRANSFER_资金帐户服务模拟_H
#define TRANSFER_资金帐户服务模拟_H
#include "../../../src/资金帐户BC/应用层/资金帐户服务接口.h"
class 资金帐户服务模拟: public 资金帐户服务接口{
private:
    资金帐户服务模拟(){}
    static 资金帐户服务模拟* 资金帐户请求服务_;
public:
    ~资金帐户服务模拟() {
        资金帐户服务模拟::资金帐户请求服务_= nullptr;
    }
    static 资金帐户服务模拟* 获取单例(){
        if (资金帐户请求服务_ == nullptr) {
            资金帐户请求服务_ = new 资金帐户服务模拟();
        }
        return 资金帐户请求服务_;
    }
    bool 已经到账=false;
    bool 已经退款=false;
    bool 已经扣减资金=false;
    bool 已添加资金帐户=false;
    virtual void 初始化资金(std::string 账号, float 金额) override{
    } ;
    virtual void 增加资金(int 单号,std::string 账号,float 金额) override{
        if(账号=="YY"){
            已经到账=true;
        }
        if(账号=="XX"){
            已经退款=true;
        }
    };
    virtual void 扣减资金(int 单号, std::string 账号, float 金额) override{
        已经扣减资金=true;
    };
    virtual void  设置禁止收款(std::string 账号, bool 是否禁止) override{};
    virtual void  设置禁止付款(std::string 账号, bool 是否禁止) override{};
    virtual void 添加资金帐户(std::string 账号) override{
        已添加资金帐户=true;
    };
    virtual boost::optional<资金帐户> 获取资金帐户(std::string 账号) override{
        return boost::none;
    };
};


#endif //TRANSFER_资金帐户服务模拟_H
