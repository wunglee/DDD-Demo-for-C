#ifndef TRANSFER_RequireFilterMock2_H
#define TRANSFER_RequireFilterMock2_H
#include "../../../src/framework_components/requestion_filters/filter.h"
class RequireFilterMock2 : public Filter {
 public:
  bool beforeExecute = false;
  bool afterExecute = false;
  RequireFilterMock2(std::string name) : Filter(name) {}
  virtual ~RequireFilterMock2(){};
  virtual void Before_Executing(std::string func, const boost::any parameter) override {
    beforeExecute = true;
  };
  virtual void After_Executing(
      std::string func, const boost::any parameter, Response& response) override {
    afterExecute = true;
  };
};
#endif  // TRANSFER_RequireFilterMock2_H
