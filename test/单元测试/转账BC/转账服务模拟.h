#ifndef TRANSFER_转账服务模拟_H
#define TRANSFER_转账服务模拟_H
#include "../../../src/全局配置/服务接口/转账服务接口.h"
class 转账服务模拟: public 转账服务接口{
private:
    转账服务模拟(){}
    static 转账服务模拟* 转账请求服务_;
public:
    ~转账服务模拟() {
        转账服务模拟::转账请求服务_= nullptr;
    }
    static 转账服务模拟* 获取单例(){
        if (转账请求服务_ == nullptr) {
            转账请求服务_ = new 转账服务模拟();
        }
        return 转账请求服务_;
    }
    static void 销毁单例(){
        if (转账请求服务_ != nullptr) {
            delete 转账请求服务_;
        }
    }
    bool 申请转账已调用=false;
    bool 通知退款已调用=false;
    bool 通知到账已调用=false;
    bool 通知取消已调用=false;
    bool 通知申请退款已调用=false;
    bool 通知出账已调用=false;
    virtual int 申请转账(std::string 付款账号, std::string 收款账号, float 金额) {
        申请转账已调用=true;
        return 0;
    };
    virtual void 通知到账(int 单号,std::string 账号){
        if(账号=="XX"){
            通知退款已调用=true;
        }
        if(账号=="YY"){
            通知到账已调用=true;
        }
    };
    virtual void 通知取消(int 单号,异常 异常){
        通知取消已调用=true;
    };
    virtual void 通知申请退款(int 单号,异常 异常){
        通知申请退款已调用=true;
    };
    virtual void 通知出账(int 单号){
        通知出账已调用=true;
    };
    virtual boost::optional<转账> 获取转账(int 单号) {
        return boost::none;
    }
};


#endif //TRANSFER_转账服务模拟_H
