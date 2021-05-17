//
// Created by 王立 on 2021/5/10.
//

#ifndef TRANSFER_转账查询接口_H
#define TRANSFER_转账查询接口_H


class 转账查询接口 {
public:
    virtual ~转账查询接口() {
    }
    virtual boost::optional<转账> 获取转账(int 单号)=0;
};


#endif //TRANSFER_转账查询接口_H
