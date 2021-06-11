#ifndef DDD_DEMO_FOR_C_FUND_HTTP_CLIENT_H
#define DDD_DEMO_FOR_C_FUND_HTTP_CLIENT_H

#include "../../../bc/fund/frontend_adapters/fund_http_service.h"
#include "fund_service_remote_interface.h"

class FundHttpClient : public FundServiceRemoteInterface {
  FundHttpService* fundHttpService = NamingServiceManager::GetInstance()
                                         ->Find_Service<FundHttpService*>("FundHttpService")
                                         .value();
  static FundHttpClient* fundHttpClient;
  FundHttpClient() {}

 public:
  virtual ~FundHttpClient() { fundHttpClient = nullptr; }
  static FundHttpClient* BuildInstance() {
    if (FundHttpClient::fundHttpClient == nullptr) {
      FundHttpClient::fundHttpClient = new FundHttpClient();
    }
    return FundHttpClient::fundHttpClient;
  }
  static FundHttpClient* GetInstance() { return BuildInstance(); }
  static void Destroy_Singleton() {
    if (FundHttpClient::fundHttpClient != nullptr) delete FundHttpClient::fundHttpClient;
  }
  bool LockAmount(std::string account_name, float amount) override {
    LockAmountDTO lock_Amount_DTO("0", account_name, amount);
    HttpRequest httpRequest("", lock_Amount_DTO);
    HttpResponse httpResponse = fundHttpService->LockAmount(httpRequest);
    if (!httpResponse.body.empty()) {
      return boost::any_cast<bool>(httpResponse.body);
    }
    return false;
  }
};

#endif  // DDD_DEMO_FOR_C_FUND_HTTP_CLIENT_H
