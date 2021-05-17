#include "应用层/转账服务.h"
#include "从适配器/转账查询.h"
#include "主适配器/转账事件处理器.h"
#include "从适配器/转账仓储.h"
#include "从适配器/转账DAO.h"
#include "主适配器/Protobuf请求适配器.h"

转账服务 * 转账服务::转账服务_= nullptr;
转账查询 * 转账查询::转账查询_= nullptr;
转账事件处理器 * 转账事件处理器::转账事件处理器_= nullptr;
转账仓储 * 转账仓储::转账仓储_= nullptr;
转账DAO * 转账DAO::转账DAO_= nullptr;
Protobuf请求适配器 * Protobuf请求适配器::PB请求适配器_= nullptr;