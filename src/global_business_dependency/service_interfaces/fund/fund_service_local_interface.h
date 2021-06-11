#ifndef TRANSFER_FundServiceLocalInterface_H
#define TRANSFER_FundServiceLocalInterface_H

#include <string>

#include <boost/any.hpp>

#include "boost/optional.hpp"

#include "../../../bc/fund/domain/fund.h"
#include "fund_dto.h"

class FundServiceLocalInterface {
 public:
  virtual ~FundServiceLocalInterface() {}
  virtual void Initialize(std::string account_id, float amount) = 0;
  //增加资金
  virtual void Increase(int order_no, std::string account_id, float amount) = 0;
  //预扣资金
  virtual bool LockAmount(std::string account_id, float amount) = 0;
  // 取消预扣资金
  virtual void UnLockAmount(std::string account_id, float amount) = 0;
  // 增加资金
  virtual void Decrease(int order_no, std::string account_id, float amount) = 0;
  // 设置禁止付款
  virtual void SetForbidOut(std::string account_id, bool forbid) = 0;
  // 设置禁止收款
  virtual void SetForbidIn(std::string account_id, bool forbid) = 0;
  // 添加资金帐户
  virtual void AddFundAccount(std::string account_id) = 0;
  // 获取资金帐户
  virtual boost::optional<FundDTO> GetFund(std::string account_name) = 0;
};

#endif  // TRANSFER_FundServiceLocalInterface_H
