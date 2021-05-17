#ifndef TRANSFER_转账用户_H
#define TRANSFER_转账用户_H
#include <string>

class 转账用户 {
public:
    const std::string 用户名_;
    const bool 是否冻结_;
    转账用户(const std::string 用户名_, bool 是否冻结_=false) :
    用户名_(用户名_), 是否冻结_(是否冻结_) {}
};
#endif //TRANSFER_转账用户_H
