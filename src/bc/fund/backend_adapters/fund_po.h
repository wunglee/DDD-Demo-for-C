//
// Created by 王立 on 2021/5/12.
//

#ifndef TRANSFER_FundPO_H
#define TRANSFER_FundPO_H
#include <string>

class FundPO {
public:
    FundPO(const std::string &account_id): FundPO(account_id, false, false, 0,0){
    }
    FundPO(const std::string &account_id, bool forbid_out, bool forbid_in, float free_amount, float locked_amount)
    : account_id_(account_id), forbid_out_(forbid_out), forbid_in_(forbid_in), free_amount_(free_amount), locked_amount_(locked_amount) {}
    std::string account_id_;
    bool forbid_out_ = false;
    bool forbid_in_ = false;
    float free_amount_;
    float locked_amount_;
};


#endif //TRANSFER_FundPO_H
