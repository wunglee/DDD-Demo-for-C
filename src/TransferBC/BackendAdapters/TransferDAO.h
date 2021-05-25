#ifndef TRANSFER_转账DAO_H
#define TRANSFER_转账DAO_H
#include "TransferDAOInterface.h"
#include "TransferPO.h"
class TransferDAO: public TransferDAOInterface{
private:
    std::vector<TransferPO> 转账集合_;
    static TransferDAO* 转账DAO_;
    TransferDAO() {}
public:
    ~TransferDAO() {
        TransferDAO::转账DAO_= nullptr;
        转账集合_.clear();
    }
    static TransferDAO* 构建单例(){
        if (TransferDAO::转账DAO_ == nullptr) {
            TransferDAO::转账DAO_ = new TransferDAO();
        }
        return TransferDAO::转账DAO_;
    }
    static TransferDAO * 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(TransferDAO::转账DAO_ != nullptr)
           delete TransferDAO::转账DAO_;
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


#endif //TRANSFER_转账DAO_H
