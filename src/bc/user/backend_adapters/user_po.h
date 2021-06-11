//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_UserPO_H
#define TRANSFER_UserPO_H
#include <string>

class UserPO {
public:
    std::string account_id_;
    bool frozen_;
    UserPO(const std::string &account_id, bool frozen=false)
    : account_id_(account_id), frozen_(frozen){}
};


#endif //TRANSFER_UserPO_H
