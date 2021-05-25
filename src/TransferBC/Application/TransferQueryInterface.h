//
// Created by 王立 on 2021/5/10.
//

#ifndef TRANSFER_转账查询接口_H
#define TRANSFER_转账查询接口_H


class TransferQueryInterface {
public:
    virtual ~TransferQueryInterface() {
    }
    virtual boost::optional<Transfer> 获取转账(int 单号)=0;
};


#endif //TRANSFER_转账查询接口_H
