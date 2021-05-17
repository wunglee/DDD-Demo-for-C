#ifndef TRANSFER_持久化对象_H
#define TRANSFER_持久化对象_H


class 转账PO {
public:
    long 单号;
    std::string 付款方账号;
    std::string 收款方账号;
    float 金额;
    int 状态;
    转账PO(long 单号, const std::string 付款方账号, const std::string 收款方账号,int 状态, float 金额)
    : 单号(单号), 付款方账号(付款方账号),收款方账号(收款方账号),状态(状态), 金额(金额) {}
};


#endif //TRANSFER_持久化对象_H
