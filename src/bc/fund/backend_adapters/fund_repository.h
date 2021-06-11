#ifndef TRANSFER_FundRepository_H
#define TRANSFER_FundRepository_H
#include "../application/fund_repository_interface.h"
#include "fund_po.h"
#include "fund_dao_interface.h"
#include "fund_query.h"
class FundRepository : public FundRepositoryInterface{
private:
    FundDAOInterface * fundDAOInterface_;
    static FundRepository* fundRepository_;
    FundRepository(FundDAOInterface * fundDAOInterface): fundDAOInterface_(fundDAOInterface) {}
public:
    virtual ~FundRepository() {
        FundRepository::fundRepository_= nullptr;
    }
    static FundRepository* BuildInstance(FundDAOInterface * fundDAOInterface_){
        assert(fundDAOInterface_!= nullptr);
        if (FundRepository::fundRepository_ == nullptr) {
            FundRepository::fundRepository_ = new FundRepository(fundDAOInterface_);
        }
        return FundRepository::fundRepository_;
    }
    static FundRepository* GetInstance(){
        if(FundRepository::fundRepository_ == nullptr){
            throw "单例未创建";
        }
        return FundRepository::fundRepository_;
    }
    static void DestroyInstance(){
        if(FundRepository::fundRepository_ != nullptr)
          delete FundRepository::fundRepository_;
    }
    virtual Fund GetExisted(std::string account_id)override{
        boost::optional<Fund> fund_optional= FundQuery::GetInstance()->GetFund(account_id);
        if(!fund_optional.has_value()){
            throw Exception((boost::format("没有找到资金帐户:%1%") % account_id).str());
        }
        return fund_optional.value();
    }
    virtual void Create(Fund& fund) override{
        FundPO fundPO_(fund.GetAccount(), fund.IsForbidIn(), fund.Is_Forbid_Out(), fund.Get_Free_Amount(), fund.Get_Locked_Amount());
        fundDAOInterface_->AddFundPO(fundPO_);
    }
    virtual void Update(Fund& fund) override{
        FundPO fundPO_(fund.GetAccount(), fund.IsForbidIn(), fund.Is_Forbid_Out(), fund.Get_Free_Amount(), fund.Get_Locked_Amount());
        fundDAOInterface_->UpdateFundPO(fundPO_);
    }
};


#endif //TRANSFER_FundRepository_H
