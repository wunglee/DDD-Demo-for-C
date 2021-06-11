#ifndef TRANSFER_FundRepositoryMock_H
#define TRANSFER_FundRepositoryMock_H
#include "../../../../src/bc/fund/application/fund_repository_interface.h"
class FundRepositoryMock : public FundRepositoryInterface{
private:
    std::vector<Fund> & funds;
    static FundRepositoryMock* fundRepositoryMock;
    FundRepositoryMock(std::vector<Fund> &funds): funds(funds){}
public:
    ~FundRepositoryMock() {
        FundRepositoryMock::fundRepositoryMock= nullptr;
    }
    static FundRepositoryMock* BuildInstance(std::vector<Fund> &funds){
        if (fundRepositoryMock == nullptr) {
            fundRepositoryMock = new FundRepositoryMock(funds);
        }
        return fundRepositoryMock;
    }
    virtual void Create(Fund& fund) override{
        funds.push_back(fund);
    }
    virtual void Update(Fund& fund) override{
        funds.clear();//不知道如何替换集合中的原有对象，只能简单处理】
        funds.push_back(fund);
    }
    virtual Fund GetExisted(std::string account_id)override{
          for(Fund& fund:funds){
              if(fund.GetAccount() == account_id){
                   return Fund(fund.GetAccount(),
                               fund.IsForbidIn(),
                               fund.Is_Forbid_Out(),
                               fund.Get_Free_Amount(),
                               fund.Get_Locked_Amount());
              }
          }
          throw Exception((boost::format("没有找到资金帐户:%1%") % account_id).str());
    }
};


#endif //TRANSFER_FundRepositoryMock_H
