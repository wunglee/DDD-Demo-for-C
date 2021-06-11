#ifndef TRANSFER_TansferServiceMock_H
#define TRANSFER_TansferServiceMock_H
#include "../../../../src/global_business_dependency/service_interfaces/transfer/transfer_service_interface.h"
class TansferServiceMock: public TransferServiceInterface{
private:
    TansferServiceMock(){}
    static TansferServiceMock* tansferServiceMock_;
public:
    ~TansferServiceMock() {
        TansferServiceMock::tansferServiceMock_= nullptr;
    }
    static TansferServiceMock* GetInstance(){
        if (tansferServiceMock_ == nullptr) {
            tansferServiceMock_ = new TansferServiceMock();
        }
        return tansferServiceMock_;
    }
    static void DestroyInstance(){
        if (tansferServiceMock_ != nullptr) {
            delete tansferServiceMock_;
        }
    }
    bool applyTransferExecuted=false;
    bool notifyRefundExecuted=false;
    bool notifyPayeeFundIncreasedExecuted=false;
    bool notifyCancelExecuted=false;
    bool notifyApplyRefundExecuted=false;
    bool NotifyPayerFundDeductedExecuted=false;
    virtual int ApplyTransfer(std::string payer, std::string payee, float amount) override{
        applyTransferExecuted=true;
        return 0;
    };
    virtual void NotifyFundIncreased(int id, std::string account_id) override{
        if(account_id=="XX"){
            notifyRefundExecuted=true;
        }
        if(account_id=="YY"){
            notifyPayeeFundIncreasedExecuted=true;
        }
    };
    virtual void NotifyCancel(int order_no, Exception exception)override{
        notifyCancelExecuted=true;
    };
    virtual void NotifyApplyRefund(int order_no, Exception exception)override{
        notifyApplyRefundExecuted=true;
    };
    virtual void NotifyPayerFundDeducted(int order_no)override{
        NotifyPayerFundDeductedExecuted=true;
    };
    virtual boost::optional<TransferDTO> GetTransfer(int order_no) override{
        return boost::none;
    }
};


#endif //TRANSFER_TansferServiceMock_H
