#ifndef TRANSFER_资金事件DTO_H
#define TRANSFER_资金事件DTO_H
#include <string>
struct 增资已成功DTO{
    const int 单号;
    const std::string 增资账号;
    const float 金额;
    增资已成功DTO(const int 单号, const std::string &增资账号, const float 金额)
            : 单号(单号), 增资账号(增资账号), 金额(金额) {}
};
#endif //TRANSFER_资金事件DTO_H
