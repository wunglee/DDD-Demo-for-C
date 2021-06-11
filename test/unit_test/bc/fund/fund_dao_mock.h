#ifndef TRANSFER_FundDAOMock_H
#define TRANSFER_FundDAOMock_H
#include "../../../../src/bc/fund/backend_adapters/fund_dao_interface.h"
#include "../../../../src/bc/fund/backend_adapters/fund_po.h"

class FundDAOMock : public FundDAOInterface {
    std::vector<FundPO> fundPOs;
    static FundDAOMock* fundDAOMock;
    FundDAOMock(){}
public:
    ~FundDAOMock() {
        FundDAOMock::fundDAOMock= nullptr;
        fundPOs.clear();
    }
    static FundDAOMock* BuildInstance(){
        if (fundDAOMock == nullptr) {
            fundDAOMock = new FundDAOMock();
        }
        return fundDAOMock;
    }
    virtual void AddFundPO(const FundPO& fundPO)override {
        fundPOs.push_back(fundPO);
    };
    virtual void UpdateFundPO(const FundPO& _fundPO)override{
        for(FundPO& fundPO_:fundPOs){
            if(fundPO_.account_id_ == _fundPO.account_id_){
                fundPO_.free_amount_=_fundPO.free_amount_;
                fundPO_.forbid_in_=_fundPO.forbid_in_;
                fundPO_.forbid_out_=_fundPO.forbid_out_;
            }
        }
    };
    virtual boost::optional<FundPO>  GetFundPO(const std::string account_id)override{
        for(FundPO& fundPO_:fundPOs){
            if(fundPO_.account_id_ == account_id){
                return fundPO_;
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_FundDAOMock_H
