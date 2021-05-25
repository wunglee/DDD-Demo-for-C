#ifndef TRANSFER_转账DAO模拟_H
#define TRANSFER_转账DAO模拟_H
#include "../../../src/TransferBC/BackendAdapters/TransferPO.h"
#include "../../../src/TransferBC/BackendAdapters/TransferDAOInterface.h"
class TransferDAOMock: public TransferDAOInterface{
private:
    std::vector<TransferPO> 转账集合_;
    static TransferDAOMock* 转账DAO模拟_;
    TransferDAOMock() {}
public:
    ~TransferDAOMock() {
        TransferDAOMock::转账DAO模拟_= nullptr;
        转账集合_.clear();
    }
    static TransferDAOMock* 获取单例(){
        if (转账DAO模拟_ == nullptr) {
            转账DAO模拟_ = new TransferDAOMock();
        }
        return 转账DAO模拟_;
    }
    virtual void 新增转账PO(const TransferPO &转账PO) override{
        转账集合_.push_back(转账PO);
    }
    virtual boost::optional<TransferPO> 获取转账PO(int 单号) override{
        for(TransferPO 转账PO_: 转账集合_){
           if(转账PO_.单号==单号){
               return 转账PO_;
           }
        }
        return boost::none;
    };
    virtual void 更新转账PO状态(int 单号,int 状态) override{
        for(TransferPO& 转账PO_: 转账集合_){
            if(转账PO_.单号==单号){
                转账PO_.状态=状态;
            }
        }
    };
};


#endif //TRANSFER_转账DAO模拟_H
