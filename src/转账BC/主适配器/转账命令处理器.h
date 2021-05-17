#ifndef TRANSFER_转账前端控制器_H
#define TRANSFER_转账前端控制器_H
#include "../../../src/框架组件/命令总线/命令处理器.h"
#include "../../../src/框架组件/命令总线/处理结果.h"
#include "../../../src/框架组件/命名服务/命名服务管理器.h"
#include "../../../src/转账BC/应用层/转账服务接口.h"
#include "boost/any.hpp"
#include "转账DTO.h"
class 转账命令处理器 :public 命令处理器{
private:
    转账服务接口 * 转账服务接口_= 命名服务管理器::获取单例()->查找服务<转账服务接口 *>("转账服务").value();
public:
    virtual ~转账命令处理器(){
    }
    virtual 处理结果 处理(std::string 方法名,const boost::any &方法参数) override {
        申请转账DTO 申请转账DTO_=boost::any_cast<申请转账DTO>(方法参数);
        处理结果 处理结果_;
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
