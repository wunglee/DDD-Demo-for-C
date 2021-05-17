//
// Created by 王立 on 2021/5/17.
//

#ifndef TRANSFER_用户服务工厂_H
#define TRANSFER_用户服务工厂_H
#include "应用层/用户服务.h"
#include "从适配器/用户仓储.h"
#include "从适配器/用户查询.h"
#include "从适配器/用户DAO.h"

class 用户服务工厂 {
public:
    static 用户服务接口 *获取单例() {
        return 用户服务::构建单例(
                用户仓储::构建单例(用户DAO::构建单例()),
                   用户查询::构建单例(用户DAO::构建单例()));
    }
    static void 销毁单例() {
        用户DAO::销毁单例();
        用户仓储::销毁单例();
        用户查询::销毁单例();
        用户服务::销毁单例();
    }
};


#endif //TRANSFER_用户服务工厂_H
