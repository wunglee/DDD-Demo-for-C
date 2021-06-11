#ifndef TRANSFER_Fund_H
#define TRANSFER_Fund_H
#include "boost/format.hpp"
#include "../../../framework_components/exception.h"
class Fund {
private:
    std::string account_id_;
    bool forbid_in_ = false;
    bool forbid_out_ = false;
    float free_amount_=0;
    float locked_amount_=0;
public:
    Fund(const std::string &account_id) : account_id_(account_id) {}

    Fund(const std::string &account_id, bool forbid_in, bool forbid_out, float free_amount, float locked_amount)
    : account_id_(account_id), forbid_in_(forbid_in), forbid_out_(forbid_out), free_amount_(free_amount),locked_amount_(locked_amount) {}

    const std::string GetAccount() const {
        return account_id_;
    }

    void AddAmount(float amount) {
        free_amount_ += amount;
    }

    void SubAmount(float amount) {
        if (Is_Enough(amount)) {
            free_amount_ -= amount;
        } else {
            throw Exception((boost::format("余额不足，无法扣减金额:%s") % amount).str());
        }
    }

    void SetForbidIn(bool Forbid_In) {
        forbid_in_ = Forbid_In;
    }

    void SetForbidOut(bool Forbid_Out) {
        forbid_out_ = Forbid_Out;
    }

    bool IsForbidIn() const {
        return forbid_in_;
    }

    bool Is_Forbid_Out() const {
        return forbid_out_;
    }

    float Is_Enough(float amount) {
        return free_amount_ >= amount;
    }

    float Get_Amount() const {
        return free_amount_+locked_amount_;
    }
    float Get_Free_Amount() const {
        return free_amount_;
    }
    float Get_Locked_Amount() const {
        return locked_amount_;
    }
    bool Lock_Amount(float amount){
        if(free_amount_>amount){
            locked_amount_+=amount;
            free_amount_-=amount;
            return true;
        }
        return false;
    }
    void UnLock_Amount(float amount){
        if(free_amount_<=amount){
            free_amount_=locked_amount_+free_amount_;
            locked_amount_=0;
        }else{
            locked_amount_-=amount;
            free_amount_+=amount;
        }
    }
};
#endif //TRANSFER_Fund_H
