#pragma once
#include <string>

#include <boost/any.hpp>

#include "boost/optional.hpp"

#include "fund_dto.h"

// 资金帐户服务接口
class FundServiceInterface {
 public:
  virtual ~FundServiceInterface() {}
  virtual int Initialize(const std::string& account_id, float amount) = 0;

  /**
   * @brief 增加资金
   * @param order_no 单号
   * @param account_id 帐号
   * @param amount 金额
   **/
  virtual int Increase(int order_no, const std::string& account_id, float amount) = 0;

  /**
   * @brief 增加资金
   * @param order_no 单号
   * @param account_id 帐号
   * @param amount 金额
   **/
  virtual int Decrease(int order_no, const std::string& account_id, float amount) = 0;

  // 设置禁止收款
  virtual int SetForbidIn(const std::string& account_id, bool forbid_in) = 0;

  // 设置禁止付款
  virtual int SetForbidOut(const std::string& account_id, bool forbid_out) = 0;

  // 添加资金帐户
  virtual int AddFundAccount(const std::string& account_id) = 0;

  // 获取资金帐户
  virtual int GetFund(const std::string& account_id, FundDTO& fund_dto) = 0;
};
