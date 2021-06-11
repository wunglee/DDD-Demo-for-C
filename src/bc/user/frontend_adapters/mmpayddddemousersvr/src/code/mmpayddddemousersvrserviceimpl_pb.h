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

#include "mmtenpay/mmpaybasic/mmpayerrorcode/mmpayerrorapi/mmpayerrorapi.h"

#include "mmpayddddemousersvr.pb.h"
#include "sk_mmpayddddemousersvrservice.pb.h"

/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-service-h-headers][头文件] // NOLINT
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
  
// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-service-h-headers][头文件] // NOLINT
/* clang-format on */

class MMPayDDDDemoUserSvrConfig;

class MMPayDDDDemoUserSvrServiceImpl_PB : public MMPayDDDDemoUserSvrService_PB {
 public:
  explicit MMPayDDDDemoUserSvrServiceImpl_PB(MMPayDDDDemoUserSvrConfig* config);
  virtual ~MMPayDDDDemoUserSvrServiceImpl_PB();

  virtual int CheckRequest(Comm::QQMAILMSGHEAD* header, Comm::SKBuffer* buffer);

  virtual int SKUserDefinedOper(const unsigned int head_uin,
                                const tlvpickle::SKBuiltinBytes_PB& req,
                                tlvpickle::SKBuiltinBytes_PB& resp);

  virtual int SKEcho(const unsigned int head_uin, const tlvpickle::SKBuiltinEchoInfo_PB& req,
                     tlvpickle::SKBuiltinEchoInfo_PB& resp);

  virtual int AddUser(const uint32_t head_uin, const mmpayddddemousersvr::AddUserReq& req,
                      mmpayddddemousersvr::AddUserResp& resp);

  virtual int FreezeUser(const uint32_t head_uin, const mmpayddddemousersvr::FreezeUserReq& req,
                         mmpayddddemousersvr::FreezeUserResp& resp);

  virtual int UnFreezeUser(const uint32_t head_uin, const mmpayddddemousersvr::UnFreezeUserReq& req,
                           mmpayddddemousersvr::UnFreezeUserResp& resp);

  virtual int IsFrozen(const uint32_t head_uin, const mmpayddddemousersvr::IsFrozenReq& req,
                       mmpayddddemousersvr::IsFrozenResp& resp);

  virtual int GetUser(const uint32_t head_uin, const mmpayddddemousersvr::GetUserReq& req,
                      mmpayddddemousersvr::GetUserResp& resp);

  /* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-service-h-member][自定义成员变量及方法] // NOLINT
  /* clang-format on */
  // ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

  // ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
  /* clang-format off */
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-service-h-member][自定义成员变量及方法] // NOLINT
  /* clang-format on */

 private:
  MMPayDDDDemoUserSvrConfig* config_;
  mmpayerrorapi::ErrorReporterMgr err_reporter_mgr;
};
