#ifndef TRANSFER_FundDAO_H
#define TRANSFER_FundDAO_H
#include "fund_dao_interface.h"
class FundMenoryDAO: public FundDAOInterface {
private:
    static FundMenoryDAO* fundDao_;
    std::vector<FundPO> fundPOs;
public:
    virtual ~FundMenoryDAO() {
        FundMenoryDAO::fundDao_= nullptr;
        fundPOs.clear();
    }
    static FundMenoryDAO* BuildInstance(){
        if (FundMenoryDAO::fundDao_ == nullptr) {
            FundMenoryDAO::fundDao_ = new FundMenoryDAO();
        }
        return FundMenoryDAO::fundDao_;
    }
    static FundMenoryDAO* GetInstance(){
        return BuildInstance();
    }
    static void DestroyInstance(){
        if(FundMenoryDAO::fundDao_ != nullptr)
          delete FundMenoryDAO::fundDao_;
    }
    virtual void AddFundPO(const FundPO& fundPO) override {
        fundPOs.push_back(fundPO);
    };
    virtual void UpdateFundPO(const FundPO& _fundPO) override{
        for(FundPO& fundPO_:fundPOs){
            if(fundPO_.account_id_ == _fundPO.account_id_){
                fundPO_.free_amount_=_fundPO.free_amount_;
                fundPO_.locked_amount_=_fundPO.locked_amount_;
                fundPO_.forbid_in_=_fundPO.forbid_in_;
                fundPO_.forbid_out_=_fundPO.forbid_out_;
            }
        }
    } ;
    virtual boost::optional<FundPO>  GetFundPO(const std::string account_id) override{
        for(FundPO& fundPO_:fundPOs){
            if(fundPO_.account_id_ == account_id){
               return fundPO_;
            }
        }
        return boost::none;
    }
};
#endif //TRANSFER_资金帐户DAO_H
