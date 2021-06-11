#ifndef DDD_DEMO_FOR_C_FUND_SERVICE_REMOTE_INTERFACE_H
#define DDD_DEMO_FOR_C_FUND_SERVICE_REMOTE_INTERFACE_H
#include "../../../framework_components/network_protocol/http.h"
class FundServiceRemoteInterface {
public:
    /**
     * @brief 预扣资金
     */
    virtual bool LockAmount(std::string account_id, float amount)=0;
};


#endif //DDD_DEMO_FOR_C_FUND_SERVICE_REMOTE_INTERFACE_H
