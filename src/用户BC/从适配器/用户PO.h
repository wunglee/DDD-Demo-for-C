//
// Created by 王立 on 2021/5/13.
//

#ifndef TRANSFER_用户PO_H
#define TRANSFER_用户PO_H


class 用户PO {
public:
    bool 是否冻结_;
    std::string 账号_;
    用户PO(const std::string &账号,bool 是否冻结=false)
    :  账号_(账号),是否冻结_(是否冻结){}
};


#endif //TRANSFER_用户PO_H
