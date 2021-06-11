#ifndef DDD_DEMO_FOR_C_FUND_HTTP_SERVICE_H
#define DDD_DEMO_FOR_C_FUND_HTTP_SERVICE_H

#include "../../../framework_components/requestion_filters/require_interceptor.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_dto.h"
#include "../../../global_business_dependency/service_interfaces/fund/fund_service_remote_interface.h"

class FundHttpService {
 private:
  RequireInterceptor* require_Interceptor_ = nullptr;
  static FundHttpService* fundHttpService;
  FundHttpService(RequireInterceptor* require_Interceptor)
      : require_Interceptor_(require_Interceptor) {}

 public:
  ~FundHttpService() { fundHttpService = nullptr; }

  static FundHttpService* BuildInstance(RequireInterceptor* require_Interceptor) {
    if (FundHttpService::fundHttpService == nullptr) {
      FundHttpService::fundHttpService = new FundHttpService(require_Interceptor);
    }
    return FundHttpService::fundHttpService;
  }

  static FundHttpService* GetInstance() {
    if (FundHttpService::fundHttpService == nullptr) {
      throw "实例未创建";
    }
    return FundHttpService::fundHttpService;
  }

  static void Destroy_Singleton() {
    if (FundHttpService::fundHttpService != nullptr) delete FundHttpService::fundHttpService;
  }
  HttpResponse LockAmount(HttpRequest& httpRequest) {
    LockAmountDTO lockAmountDTO = boost::any_cast<LockAmountDTO>(httpRequest.body);
    Require require(lockAmountDTO.order_no_, "FundRequireMapping", "lock_amount", lockAmountDTO);
    Response response = require_Interceptor_->Commit(require);
    return HttpResponse(boost::any_cast<bool>(response.value));
  }
};
#endif  // DDD_DEMO_FOR_C_FUND_HTTP_SERVICE_H
