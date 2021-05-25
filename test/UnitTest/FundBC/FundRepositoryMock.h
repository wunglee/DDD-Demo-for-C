#ifndef TRANSFER_资金帐户仓储模拟_H
#define TRANSFER_资金帐户仓储模拟_H
#include "../../../src/FundBC/Application/FundRepositoryInterface.h"
class FundRepositoryMock : public FundRepositoryInterface{
private:
    std::vector<Fund> & 资金帐户集合_;
    static FundRepositoryMock* 资金帐户仓储模拟_;
    FundRepositoryMock(std::vector<Fund> &资金帐户集合): 资金帐户集合_(资金帐户集合){}
public:
    ~FundRepositoryMock() {
        FundRepositoryMock::资金帐户仓储模拟_= nullptr;
    }
    static FundRepositoryMock* 构建单例(std::vector<Fund> &资金帐户集合){
        if (资金帐户仓储模拟_ == nullptr) {
            资金帐户仓储模拟_ = new FundRepositoryMock(资金帐户集合);
        }
        return 资金帐户仓储模拟_;
    }
    static FundRepositoryMock* 获取已存在的单例(){
        return 资金帐户仓储模拟_;
    }
    virtual void 新增资金帐户(Fund& 资金帐户) override{
        资金帐户集合_.push_back(资金帐户);
    }
    virtual void 更新资金帐户(Fund& _资金帐户) override{
        for(Fund& 资金帐户_:资金帐户集合_){
            if(资金帐户_.获取账号()==_资金帐户.获取账号()){
                //不知道如何替换集合中的原有对象，只能替换原有对象的内容
                资金帐户_.设置禁止转出(_资金帐户.是否禁止转出());
                资金帐户_.设置禁止转入(_资金帐户.是否禁止转入());
                //并且不能破坏原有对象的封装，导致很丑的代码
                资金帐户_.扣减金额(资金帐户_.获取金额());
                资金帐户_.增加金额(_资金帐户.获取金额());
            }
        }
    }
    virtual Fund 获取必须存在的资金帐户(std::string 账号)override{
          for(Fund& 资金帐户_:资金帐户集合_){
              if(资金帐户_.获取账号()==账号){
                   return Fund(资金帐户_.获取账号(),
                               资金帐户_.是否禁止转出(),
                               资金帐户_.是否禁止转入(),
                               资金帐户_.获取金额());
              }
          }
          throw Exception((boost::format("没有找到资金帐户:%1%") % 账号).str());
    }
};


#endif //TRANSFER_资金帐户仓储模拟_H
