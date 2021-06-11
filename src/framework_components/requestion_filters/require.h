#ifndef TRANSFER_Require_H
#define TRANSFER_Require_H
#include <list>
#include <string>

#include "boost/any.hpp"

#include "response.h"
class Require {
 private:
  std::string id_;
  std::string mapping_name_;
  std::string function_name_;
  boost::any parameters_;
  std::list<std::string> filter_config_;

 public:
  Require(
      const std::string id,
      const std::string mapping_name,
      const std::string function,
      const boost::any& parameters,
      const std::list<std::string>& filter_config = {})
      : id_(id),
        mapping_name_(mapping_name),
        function_name_(function),
        parameters_(parameters),
        filter_config_(filter_config) {}

  const std::string Get_Id() const { return id_; }

  const std::string Get_Mapping_Name() const { return mapping_name_; }

  const std::string Get_Function_Name() const { return function_name_; }

  const boost::any Get_Parameters() const { return parameters_; }

  const std::list<std::string> Get_Filter_Config() const { return filter_config_; }
};
#endif  // TRANSFER_Require_H
