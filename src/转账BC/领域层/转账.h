#ifndef ARGS_转账_H
#define ARGS_转账_H
#include "../../框架组件/异常.h"
#include "stdlib.h"
#include <boost/format.hpp>
#include "转账用户.h"

class 转账 {
public:
    enum 状态{已创建,已取消,已出账,已到账,退款中,已退回};
private:
    int 单号_;
    转账用户 付款方_;
    转账用户 收款方_;
    状态 状态_;
    float 金额_;
    void 检查帐户状态(转账用户 &转账用户){
        if(转账用户.是否冻结_){
            throw 异常((boost::format("帐户已经冻结:%s")%转账用户.用户名_).str());
        }
    }
    转账(转账用户 &付款方, 转账用户 &收款方, float 金额,转账::状态 状态=已创建,int 单号=rand()) :
            单号_(单号), 付款方_(付款方), 收款方_(收款方), 状态_(状态), 金额_(金额) {
        检查帐户状态(付款方);
        检查帐户状态(收款方);
    }
public:
    static 转账 构造新的转账(转账用户 付款方, 转账用户 收款方, float 金额) {
        return 转账(付款方,收款方,金额);
    }
    static 转账 构造旧的转账(int 单号,转账用户 付款方,转账用户 收款方,float 金额,状态 状态){
        return 转账(付款方,收款方,金额,状态,单号);
    }
    const int 获取单号() const {
        return 单号_;
    }
    const std::string 获取付款方账号() const {
        return 付款方_.用户名_;
    }
    const std::string 获取收款方账号() const {
        return 收款方_.用户名_;
    }
    状态 获取状态() const {
        return 状态_;
    }
    void 付款出账() {
        if(状态_ == 已创建){
            状态_=已出账;
        }else{
            throw 异常("状态不在申请中状态，无法设置已出账状态");
        }
    }
    void 付款到账() {
        if(状态_==已出账){
            状态_=已到账;
        }else{
            throw 异常("状态不在付款出账中状态，无法设置已到账状态");
        }
    }
    void 取消(异常 原因) {
        if(状态_ == 已创建){
            状态_=已取消;
        }else{
            throw 异常("状态不在申请中状态，无法取消");
        }
    }
    void 申请退款(异常 原因) {
        if(状态_==已出账){
            状态_=退款中;
        }else{
            throw 异常("状态不在付款出账中状态，无法设置退款中状态");
        }
    }
    void 完成退款() {
        if(状态_==退款中){
            状态_=已退回;
        }else{
            throw 异常("状态不在付款退款中状态，无法设置已退回状态");
        }
    }
    float 获取金额() const {
        return 金额_;
    }
    void 更新状态(状态 状态){
        状态_=状态;
    }
};
#endif //ARGS_转账_H
