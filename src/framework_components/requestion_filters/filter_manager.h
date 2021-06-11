#pragma once

#include <list>
#include <stack>
#include <string>

#include "boost/any.hpp"

#include "requestion_filters/filter.h"
#include "requestion_filters/require_mapping.h"
#include "requestion_filters/response.h"

// 过滤器管理器
class FilterManager {
 public:
  FilterManager(const std::list<::Filter*>& filters) : filters_(filters) {}

  /**
   * @brief 拦截处理
   * @param filter_name 请求处理器_
   * @param func_name 方法名
   * @param param 参数
   * @param filter_config 过滤器配置
   **/
  Response Filter(
      RequireMapping& require_mapping,
      const std::string& func_name,
      const boost::any& param,
      const std::list<std::string>& filter_config) {
    Response response;
    std::stack<::Filter*> call_stack;
    BeforeProcess(func_name, param, filter_config, call_stack);
    response = require_mapping.Process(func_name, param);
    response = AfterProcess(func_name, param, response, call_stack);

    return response;
  }

 private:
  /**
   * @brief 前置拦截
   * @param func_name 方法名
   * @param param 参数
   * @param filter_config 过滤器配置
   * @param call_stack 调用栈
   **/
  void BeforeProcess(
      const std::string& func_name,
      const boost::any& param,
      const std::list<std::string>& filter_config,
      std::stack<::Filter*>& call_stack) {
    for (::Filter* filter : filters_) {
      if (NeedFilter(filter->name_, filter_config)) {
        filter->BeforeProcess(func_name, param);
        call_stack.push(filter);
      }
    }
  }

  /**
   * @brief 后置拦截
   * @param func_name 方法名
   * @param param 参数
   * @param response 处理结果_
   * @param call_stack 调用栈
   **/
  Response& AfterProcess(
      const std::string& func_name,
      const boost::any& param,
      Response& response,
      std::stack<::Filter*>& call_stack) const {
    while (!call_stack.empty()) {
      call_stack.top()->AfterProcess(func_name, param, response);
      call_stack.pop();
    }
    return response;
  }

  /**
   * @brief 是否需要拦截
   * @param filter_name 过滤器名称
   * @param filter_config 过滤器配置
   **/
  bool NeedFilter(const std::string& filter_name, const std::list<std::string>& filter_config) {
    for (const auto& name : filter_config) {
      if (name == filter_name) {
        return true;
      }
    }

    return false;
  }

 private:
  std::list<::Filter*> filters_;  // 过滤器链表
};
