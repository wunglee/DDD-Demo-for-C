//
// Created by 王立 on 2021/5/17.
//

#ifndef TRANSFER_用户服务工厂_H
#define TRANSFER_用户服务工厂_H
#include "Application/UserService.h"
#include "BackendAdapters/UserRepository.h"
#include "BackendAdapters/UserQuery.h"
#include "BackendAdapters/UserDAO.h"

class UserServiceFactory {
public:
    static UserServiceInterface *获取单例() {
        return UserService::构建单例(
                UserRepository::构建单例(UserDAO::构建单例()),
                UserQuery::构建单例(UserDAO::构建单例()));
    }
    static void 销毁单例() {
        UserDAO::销毁单例();
        UserRepository::销毁单例();
        UserQuery::销毁单例();
        UserService::销毁单例();
    }
};


#endif //TRANSFER_用户服务工厂_H
