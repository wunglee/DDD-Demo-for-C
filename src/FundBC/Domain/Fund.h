#ifndef TRANSFER_资金帐户_H
#define TRANSFER_资金帐户_H
#include "boost/format.hpp"
#include "../../FrameworkComponents/Exception.h"
class Fund {
private:
    std::string 账号_;
    bool 禁止转出_ = false;
    bool 禁止转入_ = false;
    float 金额_;
public:
    Fund(const std::string &账号) : 账号_(账号) {}

    Fund(const std::string &账号, bool 禁止转出, bool 禁止转入, float 金额)
    : 账号_(账号), 禁止转出_(禁止转出), 禁止转入_(禁止转入), 金额_(金额) {}

    const std::string 获取账号() const {
        return 账号_;
    }

    void 增加金额(float 金额) {
        金额_ += 金额;
    }

    void 扣减金额(float 金额) {
        if (是否足额(金额)) {
            金额_ -= 金额;
        } else {
            throw Exception((boost::format("余额不足，无法扣减金额:%s") % 金额).str());
        }
    }

    void 设置禁止转出(bool 禁止转出) {
        禁止转出_ = 禁止转出;
    }

    void 设置禁止转入(bool 禁止转入) {
        禁止转入_ = 禁止转入;
    }

    bool 是否禁止转出() const {
        return 禁止转出_;
    }

    bool 是否禁止转入() const {
        return 禁止转入_;
    }

    float 是否足额(float 金额) {
        return 金额_ >= 金额;
    }

    float 获取金额() const {
        return 金额_;
    }
};
#endif //TRANSFER_资金帐户_H
