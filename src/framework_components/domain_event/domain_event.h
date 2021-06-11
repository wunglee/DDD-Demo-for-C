#ifndef ARGS_DomainEvent_H
#define ARGS_DomainEvent_H
#include <string>

#include "boost/any.hpp"
class DomainEvent {
 public:
  DomainEvent(std::string name, long transaction_id, std::string content)
      : name_(name), transaction_id_(transaction_id), content_(content) {}
  std::string Get_Name() const { return name_; }
  int Get_Transaction_Id() const { return transaction_id_; }
  const std::string Get_Content() const { return content_; }

 private:
  std::string name_;
  long transaction_id_;
  std::string content_;  // 业务自己序列化及返序列化
};
#endif  // ARGS_DomainEvent_H
