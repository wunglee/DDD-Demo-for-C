#ifndef TRANSFER_FundQueryMock_H
#define TRANSFER_FundQueryMock_H
#include "../../../../src/bc/fund/application/fund_service_query_interface.h"
class FundQueryMock : public FundServiceQueryInterface {
private:
    std::vector<Fund> &funds;
    static FundQueryMock* fundQueryMock;
    FundQueryMock(std::vector<Fund> &funds): funds(funds) {}
public:
    ~FundQueryMock() {
        FundQueryMock::fundQueryMock= nullptr;
        funds.clear();
    }
    static FundQueryMock* BuildInstance(std::vector<Fund> &funds){
        if (fundQueryMock == nullptr) {
            fundQueryMock = new FundQueryMock(funds);
        }
        return fundQueryMock;
    }
    virtual boost::optional<Fund> GetFund(std::string account_id) override{
            for(Fund& fund:funds){
                if(fund.GetAccount() == account_id){
                    return Fund(fund.GetAccount(),
                                fund.IsForbidIn(),
                                fund.Is_Forbid_Out(),
                                fund.Get_Free_Amount(),
                                fund.Get_Locked_Amount());
                }
            }
        return boost::none;
    }
};

#endif //TRANSFER_FundQueryMock_H
