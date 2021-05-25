#ifndef ARGS_异常_H
#define ARGS_异常_H
#include <string>
class Exception {
    std::string 消息_;
public:
   Exception(std::string 消息): 消息_(消息){}
   std::string 获取消息();
};
#endif //ARGS_异常_H
