#ifndef TRANSFER_RequireFilterMock1_H
#define TRANSFER_RequireFilterMock1_H
#include "../../../src/framework_components/requestion_filters/filter.h"
class RequireFilterMock1 : public Filter {
 public:
  bool beforeExecute = false;
  bool afterExecute = false;
  RequireFilterMock1(std::string name) : Filter(name) {}
  virtual ~RequireFilterMock1(){};
  virtual void Before_Executing(std::string function_name, const boost::any parameters) override {
    beforeExecute = true;
  };
  virtual void After_Executing(
      std::string function_name, const boost::any parameters, Response& response) override {
    afterExecute = true;
  };
};

#endif  // TRANSFER_RequireFilterMock1_H
