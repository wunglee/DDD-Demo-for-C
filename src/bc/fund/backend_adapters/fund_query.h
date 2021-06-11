#ifndef TRANSFER_FundQuery_H
#define TRANSFER_FundQuery_H
#include "../application/fund_service_query_interface.h"
#include "fund_po.h"
#include "fund_dao_interface.h"
class FundQuery : public FundServiceQueryInterface {
private:
    FundDAOInterface * fundDAOInterface_;
    static FundQuery* fundQuery_;
    FundQuery(FundDAOInterface * fundDAOInterface): fundDAOInterface_(fundDAOInterface) {}
public:
    virtual ~FundQuery() {
        FundQuery::fundQuery_= nullptr;
    }
    static FundQuery* BuildInstance(FundDAOInterface * fundDAOInterface_){
        assert(fundDAOInterface_!= nullptr);
        if (FundQuery::fundQuery_ == nullptr) {
            FundQuery::fundQuery_ = new FundQuery(fundDAOInterface_);
        }
        return FundQuery::fundQuery_;
    }
    static FundQuery* GetInstance(){
        if(FundQuery::fundQuery_ == nullptr){
            throw "单例未创建";
        }
        return FundQuery::fundQuery_;
    }
    static void DestroyInstance(){
        if(FundQuery::fundQuery_ != nullptr)
           delete FundQuery::fundQuery_;
    }
    virtual boost::optional<Fund> GetFund(std::string account_id) override{
        boost::optional<FundPO>  fundPO_ = fundDAOInterface_->GetFundPO(account_id);
        if(fundPO_.has_value()){
                return Fund(fundPO_.value().account_id_,
                            fundPO_.value().forbid_out_,
                            fundPO_.value().forbid_in_,
                            fundPO_.value().free_amount_,
                            fundPO_.value().locked_amount_);
        }
        return boost::none;
    }
};
#endif //TRANSFER_FundQuery_H
