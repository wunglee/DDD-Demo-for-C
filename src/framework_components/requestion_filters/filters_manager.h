#ifndef TRANSFER_FiltersManager_H
#define TRANSFER_FiltersManager_H
#include <list>
#include <stack>

#include "boost/any.hpp"

#include "filter.h"
#include "require_mapping.h"
#include "response.h"
class FiltersManager {
 private:
  std::list<Filter*> filters_;
  void Before_Executing(
      std::string function_name,
      const boost::any& parameters,
      const std::list<std::string>& filter_config,
      std::stack<Filter*>& used_filters) {
    for (Filter* filter : filters_) {
      if (Is_My_filter(filter->name_, filter_config)) {
        filter->Before_Executing(function_name, parameters);
        used_filters.push(filter);
      }
    }
  };
  Response& After_Executing(
      std::string function_name,
      const boost::any& parameters,
      Response& response,
      std::stack<Filter*>& used_filters) const {
    while (!used_filters.empty()) {
      used_filters.top()->After_Executing(function_name, parameters, response);
      used_filters.pop();
    }
    return response;
  }
  bool Is_My_filter(std::string filter_name, const std::list<std::string>& filter_config) {
    for (std::string config : filter_config) {
      if (config == filter_name) {
        return true;
      }
    }
    return false;
  }

 public:
  FiltersManager(const std::list<Filter*>& filters) : filters_(filters) {}
  Response Handle(
      RequireMapping& require_Mapping,
      std::string function_name,
      const boost::any& parameters,
      const std::list<std::string>& filter_config) {
    try {
      Response response;
      std::stack<Filter*> used_filters;
      Before_Executing(function_name, parameters, filter_config, used_filters);
      response = require_Mapping.handle(function_name, parameters);
      return After_Executing(function_name, parameters, response, used_filters);
    } catch (Exception exception) {
      Response response;
      response.value = boost::none;
      response.exception = std::make_shared<Exception>(exception);
      return response;
    }
  }
};

#endif  // TRANSFER_FiltersManager_H
