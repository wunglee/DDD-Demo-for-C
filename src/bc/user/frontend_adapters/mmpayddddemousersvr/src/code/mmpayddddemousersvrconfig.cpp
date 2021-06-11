// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1
/**
 * 该文件由 【瓦特】 工具生成
 * 生成器ID: xwatt-application-server
 * 生成器版本: v1.0.1
 * 生成器代码仓库：git@git.code.oa.com:wxpay-xwatt-generator/xwatt-application-server.git
 * 生成器代码版本： b5f5627e
 **/
#include "mmpay/mmpayxwatt/xwatt/log/logger.h"

#include "iFileFunc.h"
#include "mmpayddddemousersvrconfig.h"

/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-config-cpp-headers][自定义头文件] // NOLINT
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-config-cpp-headers][自定义头文件] // NOLINT
/* clang-format on */

using namespace Comm;

MMPayDDDDemoUserSvrConfig::MMPayDDDDemoUserSvrConfig() {
  server_config_ = new Comm::CEpollServerConfig;
  is_server_read_only_ = 0;
}

MMPayDDDDemoUserSvrConfig::~MMPayDDDDemoUserSvrConfig() {
  if (server_config_) {
    delete server_config_;
    server_config_ = NULL;
  }
}

Comm::CEpollServerConfig* MMPayDDDDemoUserSvrConfig::GetEpollConfig() { return server_config_; }

int MMPayDDDDemoUserSvrConfig::ReadConfig(const char* config_file) {
  if (!config_file) {
    XLOG_ERR("ReadConfig", -1, "Config is emtpy | File=%s", config_file);
    return -1;
  }

  int ret = 0;
  ret = server_config_->Read(config_file);
  if (ret != 0) {
    XLOG_ERR("ReadConfig", ret, "ReadConfig fail | FileName=%s", config_file);
    return ret;
  }

  CConfig config(config_file);
  ret = config.Init();
  if (ret != 0) {
    XLOG_ERR("ReadConfig", ret, "CConfig Init fail | FileName=%s", config_file);
    return ret;
  }

  ConfigItemInfoEx_t infoArray[] = {
      CONFIG_ITEM_EX_INT("General", "ServerReadOnly", is_server_read_only_, "0"),
      CONFIG_ITEM_EX_END};

  ret = Comm::ConfigRead(&config, infoArray);
  if (ret != 0) {
    XLOG_ERR("ReadConfig", ret, "ConfigRead failed");
  }
  Comm::ConfigDump(infoArray);

  /* clang-format off */
  //// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-config-cpp-logic][自定义逻辑] // NOLINT
  // ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
  
  // ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
  //// XWATT-TAG-END:[flow][mmpayddddemousersvr-config-cpp-logic][自定义逻辑] // NOLINT
  /* clang-format on */

  return ret;
}

/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-config-cpp-custom][自定义方法] // NOLINT
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-config-cpp-custom][自定义方法] // NOLINT
/* clang-format on */
