#ifndef DDD_DEMO_FOR_C_FUND_SERVICE_MOCK_H
#define DDD_DEMO_FOR_C_FUND_SERVICE_MOCK_H
#include "../../../../src/global_business_dependency/service_interfaces/fund/fund_service_remote_interface.h"

class FundServiceRemoteMock : public FundServiceRemoteInterface {
 private:
  bool locked_ = true;
  static FundServiceRemoteMock* fund_Service_Remote_Mock;
  FundServiceRemoteMock() {}

 public:
  virtual ~FundServiceRemoteMock() { FundServiceRemoteMock::fund_Service_Remote_Mock = nullptr; }
  static FundServiceRemoteMock* GetInstance() {
    if (fund_Service_Remote_Mock == nullptr) {
      fund_Service_Remote_Mock = new FundServiceRemoteMock();
    }
    return fund_Service_Remote_Mock;
  }
  static void DestroySingleton() {
    if (fund_Service_Remote_Mock != nullptr) {
      delete fund_Service_Remote_Mock;
    }
  }
  bool LockAmount(std::string account_name, float amount) override { return locked_; }
  void setLockedfail() { locked_ = false; }
};

#endif  // DDD_DEMO_FOR_C_FUND_SERVICE_MOCK_H
