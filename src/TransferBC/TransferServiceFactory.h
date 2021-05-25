#ifndef TRANSFER_转帐服务工厂_H
#define TRANSFER_转帐服务工厂_H
#include "BackendAdapters/TransferRepository.h"
#include "BackendAdapters/TransferDAO.h"
#include "Application/TransferService.h"
#include "BackendAdapters/TransferQuery.h"
#include "BackendAdapters/UserHttpClient.h"

class TransferServiceFactory {
public:
    static UserServiceInterface* 用户服务接口_;
    static TransferServiceInterface * 获取单例() {
        TransferRepositoryInterface * 转账仓储接口_= TransferRepository::构建单例(TransferDAO::构建单例(), UserHttpClient::获取单例());
        TransferQueryInterface * 转账查询接口_= TransferQuery::构建单例(TransferDAO::构建单例(), UserHttpClient::获取单例());
        return TransferService::构建单例(转账仓储接口_, 转账查询接口_, UserHttpClient::获取单例());
    }
    static void 销毁单例() {
        UserHttpClient::销毁单例();
        TransferDAO::销毁单例();
        TransferRepository::销毁单例();
        TransferQuery::销毁单例();
        TransferService::销毁单例();
    }
};


#endif //TRANSFER_转帐服务工厂_H
