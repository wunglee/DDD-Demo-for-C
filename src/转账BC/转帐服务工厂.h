#ifndef TRANSFER_转帐服务工厂_H
#define TRANSFER_转帐服务工厂_H
#include "从适配器/转账仓储.h"
#include "从适配器/转账DAO.h"
#include "应用层/转账服务.h"
#include "从适配器/转账查询.h"
#include "从适配器/用户HTTP客户端.h"

class 转帐服务工厂 {
public:
    static 用户服务接口* 用户服务接口_;
    static 转账服务接口 * 获取单例() {
        转账仓储接口 * 转账仓储接口_= 转账仓储::构建单例(转账DAO::构建单例(),用户HTTP客户端::获取单例());
        转账查询接口 * 转账查询接口_= 转账查询::构建单例(转账DAO::构建单例(),用户HTTP客户端::获取单例());
        return 转账服务::构建单例(转账仓储接口_, 转账查询接口_,用户HTTP客户端::获取单例());
    }
    static void 销毁单例() {
        用户HTTP客户端::销毁单例();
        转账DAO::销毁单例();
        转账仓储::销毁单例();
        转账查询::销毁单例();
        转账服务::销毁单例();
    }
};


#endif //TRANSFER_转帐服务工厂_H
