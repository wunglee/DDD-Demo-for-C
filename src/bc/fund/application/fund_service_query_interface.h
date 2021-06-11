#ifndef TRANSFER_FundServiceQueryInterface_H
#define TRANSFER_FundServiceQueryInterface_H
#include <string>

#include "boost/optional.hpp"

#include "../domain/fund.h"
class FundServiceQueryInterface {
 public:
  virtual ~FundServiceQueryInterface() {}
  virtual boost::optional<Fund> GetFund(std::string acount_id) = 0;
};

#endif  // TRANSFER_FundServiceQueryInterface_H
