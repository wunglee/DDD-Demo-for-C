#ifndef TRANSFER_FundServiceMock_H
#define TRANSFER_FundServiceMock_H
#include "../../../../src/global_business_dependency/service_interfaces/fund/fund_service_local_interface.h"
class FundServiceMock: public FundServiceLocalInterface{
private:
    FundServiceMock(){}
    static FundServiceMock* fundServiceMock;
public:
    ~FundServiceMock() {
        FundServiceMock::fundServiceMock= nullptr;
    }
    static FundServiceMock* GetInstance(){
        if (fundServiceMock == nullptr) {
            fundServiceMock = new FundServiceMock();
        }
        return fundServiceMock;
    }
    static void DestroyInstance(){
        if(fundServiceMock != nullptr)
           delete fundServiceMock;
    }
    bool amount_added=false;
    bool amount_refunded=false;
    bool amount_subed=false;
    bool account_added=false;
    bool lock_Amount=false;
    bool unlock_Amount=false;
    virtual void Initialize(std::string account_id, float amount) override{
    } ;
    virtual void Increase(int order_id, std::string account_id, float amount) override{
        if(account_id=="YY"){
            amount_added=true;
        }
        if(account_id=="XX"){
            amount_refunded=true;
        }
    };
    virtual void Decrease(int id, std::string account_id, float amount) override{
        amount_subed=true;
    };
    virtual void  SetForbidOut(std::string account_id, bool forbid) override{};
    virtual void  SetForbidIn(std::string account_id, bool forbid) override{};
    virtual void AddFundAccount(std::string account_id) override{
        account_added=true;
    };
    virtual boost::optional<FundDTO> GetFund(std::string account_id) override{
        return boost::none;
    };
    bool LockAmount(std::string account_name, float amount) override{
        lock_Amount=true;
        return lock_Amount;
    }
    void UnLockAmount(std::string account_name, float amount) override{
        unlock_Amount=true;
    }
};


#endif //TRANSFER_FundServiceMock_H
