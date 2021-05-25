#ifndef TRANSFER_资金帐户服务工厂_H
#define TRANSFER_资金帐户服务工厂_H
#include "Application/FundService.h"
#include "BackendAdapters/FundRepository.h"
#include "BackendAdapters/FundQuery.h"
#include "BackendAdapters/FundDAO.h"
#include "FrontendAdapters/FundEventMapping.h"
class FundServiceFactory {
public:
    static FundServiceInterface *获取单例(){
        FundRepositoryInterface * 资金帐户仓储接口_= FundRepository::构建单例(FundDAO::构建单例());
        FundServiceQueryInterface * 资金帐户查询接口_= FundQuery::构建单例(FundDAO::构建单例());
        return FundService::构建单例(资金帐户仓储接口_, 资金帐户查询接口_);
    }
    static void 销毁单例(){
         FundDAO::销毁单例();
         FundRepository::销毁单例();
         FundQuery::销毁单例();
         FundService::销毁单例();
    }
};
#endif //TRANSFER_资金帐户服务工厂_H
