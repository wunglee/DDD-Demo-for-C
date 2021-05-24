#include "资金帐户服务模拟.h"
#include "资金帐户DAO模拟.h"
#include "资金帐户仓储模拟.h"
#include "资金帐户查询模拟.h"

资金帐户服务模拟 * 资金帐户服务模拟::资金帐户请求服务_= nullptr;
资金帐户DAO模拟* 资金帐户DAO模拟::资金帐户DAO模拟_=nullptr;
资金帐户仓储模拟* 资金帐户仓储模拟::资金帐户仓储模拟_=nullptr;
资金帐户查询模拟* 资金帐户查询模拟::资金帐户查询模拟_=nullptr;