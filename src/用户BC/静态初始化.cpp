#include "应用层/用户服务.h"
#include "主适配器/用户事件处理器.h"
#include "从适配器/用户仓储.h"
#include "从适配器/用户DAO.h"
#include "从适配器/用户查询.h"
#include "主适配器/用户HTTP服务端.h"

用户事件处理器 * 用户事件处理器::用户事件处理器_ = nullptr;
 用户服务 * 用户服务::用户服务_ = nullptr;
 用户查询 * 用户查询::用户查询_ = nullptr;
 用户仓储* 用户仓储::用户仓储_ = nullptr;
 用户DAO* 用户DAO::单例_ = nullptr;
 用户HTTP服务端 * 用户HTTP服务端::用户HTTP服务端_= nullptr;