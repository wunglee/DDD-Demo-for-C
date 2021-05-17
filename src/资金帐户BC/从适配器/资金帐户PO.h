//
// Created by 王立 on 2021/5/12.
//

#ifndef TRANSFER_资金帐户PO_H
#define TRANSFER_资金帐户PO_H
#include <string>

class 资金帐户PO {
public:
    资金帐户PO(const std::string &账号):资金帐户PO(账号,false,false,0){
    }
    资金帐户PO(const std::string &账号, bool 禁止转出, bool 禁止转入, float 资金)
    : 账号(账号), 禁止转出_(禁止转出), 禁止转入_(禁止转入), 金额_(资金) {}
    std::string 账号;
    bool 禁止转出_ = false;
    bool 禁止转入_ = false;
    float 金额_;
};


#endif //TRANSFER_资金帐户PO_H
