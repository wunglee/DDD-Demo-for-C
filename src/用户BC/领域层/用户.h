#ifndef ARGS_用户_H
#define ARGS_用户_H
#include "../../资金帐户BC/应用层/资金帐户服务.h"
class 用户 {
private:
    bool 是否冻结_;
    std::string 账号_;
public:
    用户(const std::string &账号, bool 是否冻结=false) : 账号_(账号), 是否冻结_(是否冻结) {}

    const std::string 获取账号() const {
        return 账号_;
    }
    void 冻结() {
        是否冻结_ = true;
    }
    void 解冻() {
        是否冻结_ = false;
    }
    bool 是否冻结() const {
        return 是否冻结_;
    }
};


#endif //ARGS_用户_H
