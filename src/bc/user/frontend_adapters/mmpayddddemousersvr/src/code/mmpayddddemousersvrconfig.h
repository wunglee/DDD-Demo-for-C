// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1
/**
 * 该文件由 【瓦特】 工具生成
 * 生成器ID: xwatt-application-server
 * 生成器版本: v1.0.1
 * 生成器代码仓库：git@git.code.oa.com:wxpay-xwatt-generator/xwatt-application-server.git
 * 生成器代码版本： b5f5627e
 **/
#pragma once

#include <string>
/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-config-h-include][自定义头文件] // NOLINT
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-config-h-include][自定义头文件] // NOLINT
/* clang-format on */

namespace Comm {
class CEpollServerConfig;
}

class MMPayDDDDemoUserSvrConfig {
 public:
  MMPayDDDDemoUserSvrConfig();
  ~MMPayDDDDemoUserSvrConfig();

  Comm::CEpollServerConfig* GetEpollConfig();

  int ReadConfig(const char* config_file);

  int GetServerReadOnly();

  /* clang-format off */
  //// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-config-h-member][自定义成员变量及方法] // NOLINT
  // ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
  
  // ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
  //// XWATT-TAG-END:[flow][mmpayddddemousersvr-config-h-member][自定义成员变量及方法] // NOLINT
  /* clang-format on */

 private:
  Comm::CEpollServerConfig* server_config_;
  int is_server_read_only_;
};
