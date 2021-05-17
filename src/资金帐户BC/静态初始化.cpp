#include "应用层/资金帐户服务.h"
#include "主适配器/资金事件处理器.h"
#include "从适配器/资金帐户仓储.h"
#include "从适配器/资金帐户DAO.h"
#include "从适配器/资金帐户查询.h"
资金帐户服务 * 资金帐户服务::资金帐户服务_= nullptr;
资金事件处理器 * 资金事件处理器::资金事件处理器_= nullptr;
资金帐户仓储 * 资金帐户仓储::资金帐户仓储_= nullptr;
资金帐户DAO* 资金帐户DAO::资金帐户DAO_= nullptr;
资金帐户查询* 资金帐户查询::资金帐户查询服务_= nullptr;