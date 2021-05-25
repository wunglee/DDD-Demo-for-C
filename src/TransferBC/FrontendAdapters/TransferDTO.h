#ifndef TRANSFER_转账已创建DTO_H
#define TRANSFER_转账已创建DTO_H
#include <string>
struct 申请转账DTO {
    const std::string 付款账号;
    const std::string 收款账号;
    const float 金额;
    申请转账DTO(const std::string &付款账号, const std::string &收款账号, float 金额)
            : 付款账号(付款账号), 收款账号(收款账号), 金额(金额) {}
};

struct 转账已创建DTO{
    const int 转账单号;
    const std::string 付款方账号;
    const float 付款金额;
    转账已创建DTO(const int 转账单号, const std::string 付款方账号, float 付款金额) : 转账单号(转账单号), 付款方账号(付款方账号), 付款金额(付款金额) {}
};
struct 转账已出账DTO{
    const int 转账单号;
    const std::string 收款方账号;
    const float 金额;
    转账已出账DTO(const int 转账单号, const std::string 收款方账号, float 金额) : 转账单号(转账单号), 收款方账号(收款方账号), 金额(金额) {}
};
struct 转账已到账DTO{
    const int 单号;
    const std::string 付款方;
    const std::string 收款方;
    const float 金额;
    转账已到账DTO(const int 单号, const std::string &付款方, const std::string &收款方, const float 金额)
            : 单号(单号), 付款方(付款方),收款方(收款方), 金额(金额) {}
};
struct 转账退款事件{
    const int 单号;
    const std::string 退回账号;
    const float 金额;
    转账退款事件(const int 单号, const std::string &退回账号, const float 金额)
            : 单号(单号), 退回账号(退回账号), 金额(金额) {}
};
#endif //TRANSFER_转账已创建DTO_H
