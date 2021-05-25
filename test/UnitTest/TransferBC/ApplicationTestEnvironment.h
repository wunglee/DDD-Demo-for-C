#ifndef TRANSFER_Application测试环境_H
#define TRANSFER_Application测试环境_H
#include "../UserBC/UserServiceMock.h"
#include "../../../src/FrameworkComponents/NamingService/NamingServiceManager.h"
#include "../../../src/TransferBC/Application/TransferService.h"
#include "TransferRepositoryMock.h"
#include "TransferQueryMock.h"
class Application测试环境 : public ::testing::Test {
public:
    std::vector<Transfer> 转账集合_;
    TransferRepositoryMock * 转账仓储模拟_= nullptr;
    TransferQueryMock * 转账查询模拟_= nullptr;
    UserServiceInterface * 用户服务模拟_= nullptr;
    virtual void SetUp() {
        用户服务模拟_= UserServiceMock::构造单例();
        NamingServiceManager::获取单例()->注册服务("UserService", (UserServiceInterface *) 用户服务模拟_);
        转账仓储模拟_=TransferRepositoryMock::获取单例(转账集合_, 用户服务模拟_);
        转账查询模拟_=TransferQueryMock::获取单例(转账集合_);
        NamingServiceManager::获取单例()->注册服务("TransferService", (TransferServiceInterface *) TransferService::构建单例(转账仓储模拟_, 转账查询模拟_, 用户服务模拟_));
    }
    virtual void TearDown() {
        delete NamingServiceManager::获取单例()->注销服务<UserServiceInterface *>("UserService").value();
        NamingServiceManager::获取单例()->注销服务<TransferServiceInterface *>("TransferService").value();
        TransferService::销毁单例();
        delete 转账仓储模拟_;
        delete 转账查询模拟_;
        转账集合_.clear();
        NamingServiceManager::销毁单例();
    }
};


#endif //TRANSFER_Application测试环境_H
