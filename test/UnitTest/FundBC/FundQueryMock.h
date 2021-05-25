#ifndef TRANSFER_资金帐户查询模拟_H
#define TRANSFER_资金帐户查询模拟_H
#include "../../../src/FundBC/Application/FundServiceQueryInterface.h"
class FundQueryMock : public FundServiceQueryInterface {
private:
    std::vector<Fund> &资金帐户集合_;
    static FundQueryMock* 资金帐户查询模拟_;
    FundQueryMock(std::vector<Fund> &资金帐户集合): 资金帐户集合_(资金帐户集合) {}
public:
    ~FundQueryMock() {
        FundQueryMock::资金帐户查询模拟_= nullptr;
        资金帐户集合_.clear();
    }
    static FundQueryMock* 构建单例(std::vector<Fund> &资金帐户集合){
        if (资金帐户查询模拟_ == nullptr) {
            资金帐户查询模拟_ = new FundQueryMock(资金帐户集合);
        }
        return 资金帐户查询模拟_;
    }
    static FundQueryMock* 获取已存在的单例(){
        return 资金帐户查询模拟_;
    }
    virtual boost::optional<Fund> 获取资金帐户(std::string 账号) override{
            for(Fund& 资金帐户_:资金帐户集合_){
                if(资金帐户_.获取账号()==账号){
                    return Fund(资金帐户_.获取账号(),
                                资金帐户_.是否禁止转出(),
                                资金帐户_.是否禁止转入(),
                                资金帐户_.获取金额());
                }
            }
        return boost::none;
    }
};

#endif //TRANSFER_资金帐户查询模拟_H
