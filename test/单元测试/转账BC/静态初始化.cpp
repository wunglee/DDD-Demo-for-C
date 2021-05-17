#include "转账仓储模拟.h"
#include "转账查询模拟.h"
#include "转账服务模拟.h"
#include "用户服务模拟.h"
#include "转账DAO模拟.h"

转账服务模拟 * 转账服务模拟::转账命令服务_= nullptr;
转账仓储模拟* 转账仓储模拟::转账仓储模拟_=nullptr;
转账查询模拟* 转账查询模拟::转账查询模拟_=nullptr;
用户服务模拟* 用户服务模拟::用户服务模拟_=nullptr;
转账DAO模拟* 转账DAO模拟::转账DAO模拟_=nullptr;