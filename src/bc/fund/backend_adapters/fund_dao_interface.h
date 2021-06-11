#ifndef TRANSFER_FundDAOInterface_H
#define TRANSFER_FundDAOInterface_H
#include "boost/optional.hpp"

#include "fund_po.h"

class FundDAOInterface {
 public:
  virtual ~FundDAOInterface() {}
  virtual void AddFundPO(const FundPO& fundPO) = 0;
  virtual void UpdateFundPO(const FundPO& fundPO) = 0;
  virtual boost::optional<FundPO> GetFundPO(const std::string account_id) = 0;
};

#endif  // TRANSFER_FundDAOInterface_H
