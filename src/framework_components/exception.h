#ifndef ARGS_Exception_H
#define ARGS_Exception_H
#include <string>
class Exception {
  std::string message_;

 public:
  Exception(std::string message) : message_(message) {}
  std::string getMessage() { return message_; };
};
class Transaction_Exception : public Exception {
 public:
  Transaction_Exception(const std::string& message) : Exception(message) {}
};
#endif  // ARGS_Exception_H
