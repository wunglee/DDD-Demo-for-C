// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1
/**
 * 该文件由 【瓦特】 工具生成
 * 生成器ID: xwatt-application-server
 * 生成器版本: v1.0.1
 * 生成器代码仓库：git@git.code.oa.com:wxpay-xwatt-generator/xwatt-application-server.git
 * 生成器代码版本： b5f5627e
 **/
#include "mmpayddddemousersvrserviceimpl_pb.h"

#include "comm2/wxmesh/meshkit/clientcallobj.h"

#include "comm/mmpayddddemousersvr_itf_oss_define.h"
#include "iLog.h"
#include "iSvrkit.h"
#include "mmpay/mmpayxwatt/xwatt/log/log_reporter.h"
#include "mmpay/mmpayxwatt/xwatt/log/logger.h"
#include "mmpay/mmpayxwatt/xwatt/oss/oss_reporter.h"
#include "mmpayddddemousersvr.pb.h"
#include "mmpayddddemousersvrconfig.h"

/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][xwatt-header-for-component][依赖的其他组件头文件] // NOLINT

#include "src/framework_components/requestion_filters/response.h"
#include "src/framework_components/requestion_filters/require.h"
#include "src/framework_components/requestion_filters/require_interceptor.h"
#include "src/framework_components/idempotent/mysql_idempotent_manager.h"
#include "src/framework_components/local_transaction/mysql_transaction_manager.h"
#include "src/framework_components/domain_event/mysql_publish_subscribe_service.h"
#include "src/global_business_dependency/service_interfaces/user/user_dto.h"
#include "comm/dal_set/src/dal_set.h"
#include "comm/dal_set/src/dal_set_define.h"
#include "comm/dal_set/src/mysqlstorage.h"

//// XWATT-TAG-END:[flow][xwatt-header-for-component][依赖的其他组件头文件] // NOLINT
/* clang-format on */

/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-service-cpp-headers][自定义头文件] // NOLINT
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-service-cpp-headers][自定义头文件] // NOLINT
/* clang-format on */

using namespace Comm;
using namespace xwatt::log;
using namespace xwatt::oss;

MMPayDDDDemoUserSvrServiceImpl_PB::MMPayDDDDemoUserSvrServiceImpl_PB(
    MMPayDDDDemoUserSvrConfig* config) {
  config_ = config;
}

MMPayDDDDemoUserSvrServiceImpl_PB::~MMPayDDDDemoUserSvrServiceImpl_PB() = default;

int MMPayDDDDemoUserSvrServiceImpl_PB::CheckRequest(
    Comm::QQMAILMSGHEAD* header, Comm::SKBuffer* buffer) {
  int ret = 0;

  mmpayerrorapi::GetReporter().SetModuleid(config_->GetEpollConfig()->GetSvrPort());
  mmpayerrorapi::GetReporter().SetCmdid(header->hCmdID);

  dalset::IDBOperator* pDBOperator =
      CDAL_SET->GetDBOperator(0, 0, "mmpay_ddd_demo", "T_Idempotent", 0, false);
  if (pDBOperator == nullptr) {
    printf("CDAL_SET->GetDBOperator error.\n");
    return -10000;
  }

  std::shared_ptr<dalset::CMySqlStorage> storage = std::make_shared<dalset::CMySqlStorage>();
  storage->SetDBOperator(pDBOperator);
  MysqlIdempotentManager::GetInstance()->SetConnection(storage);
  MysqlTransactionManager::GetInstance()->SetConnection(storage);
  MysqlPublishSubscribeService::GetInstance()->SetConnection(storage);

  /* clang-format off */
  //// XWATT-TAG-BEGIN:[flow][handler-mmpayddddemousersvr-CheckRequest][CheckRequest的方法实现] // NOLINT
  /* clang-format on */
  // ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

  // ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
  /* clang-format off */
  //// XWATT-TAG-END:[flow][handler-mmpayddddemousersvr-CheckRequest][CheckRequest的方法实现] // NOLINT
  /* clang-format on */
  return ret;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::SKUserDefinedOper(
    const uint32_t head_uin,
    const tlvpickle::SKBuiltinBytes_PB& req,
    tlvpickle::SKBuiltinBytes_PB& resp) {
  XLOG_DEBUG("SKUserDefinedOper");
  return -1;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::SKEcho(
    const uint32_t head_uin,
    const tlvpickle::SKBuiltinEchoInfo_PB& req,
    tlvpickle::SKBuiltinEchoInfo_PB& resp) {
  static_cast<void>(head_uin);
  resp = req;
  return 0;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::AddUser(
    const uint32_t head_uin,
    const mmpayddddemousersvr::AddUserReq& req,
    mmpayddddemousersvr::AddUserResp& resp) {
  MeshRet stRet;
  Comm::clsRuntimeLog cost;
  cost.Start();

  std::string req_debug_string = mmpaylog::utils::FilterPrivacy4PbMsg(req).ShortDebugString();
  XLOG_RUN("AddUser Begin|Req=%s", req_debug_string.c_str());

  Require require = Require(
      std::to_string(rand()), "UserRequireMapping", "create_user", UserDTO(req.account_id()));
  Response response = RequireInterceptor::GetInstance()->Commit(require);
  if (response.exception != nullptr) {
    stRet.ret = -1000;
    resp.set_retmsg(response.exception->getMessage());
  }
  if (0 != stRet.ret) {
    XLOG_ERR(
        "AddUserAppService.Handle fail",
        stRet.ret,
        "req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  } else {
    XLOG_RUN(
        "AddUserAppService.Handle Succ|req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  }

  mmpayerrorapi::GetReporter().SetErrorcode(stRet.ret);
  uint64_t cost_time = cost.GetTimeDiffLong(true);
  //接口耗时上报
  ITF_COST_OSS_REPORT(cost_time, OSS_KEY_ITF_COST_ADDUSER);
  //接口请求上报
  ITF_REQ_OSS_REPORT(stRet.ret, OSS_KEY_ITF_REQ_ADDUSER);
  CLogReporter("mmpayddddemousersvr", __func__, stRet.ret, cost_time, req, resp);

  return stRet.ret;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::FreezeUser(
    const uint32_t head_uin,
    const mmpayddddemousersvr::FreezeUserReq& req,
    mmpayddddemousersvr::FreezeUserResp& resp) {
  MeshRet stRet;
  Comm::clsRuntimeLog cost;
  cost.Start();

  std::string req_debug_string = mmpaylog::utils::FilterPrivacy4PbMsg(req).ShortDebugString();
  XLOG_RUN("FreezeUser Begin|Req=%s", req_debug_string.c_str());

  Require require = Require("1", "UserRequireMapping", "FreezeUser", UserDTO(req.account_id()));
  Response response = RequireInterceptor::GetInstance()->Commit(require);
  if (response.exception != nullptr) {
    stRet.ret = -1000;
    resp.set_retmsg(response.exception->getMessage());
  }

  if (0 != stRet.ret) {
    XLOG_ERR(
        "FreezeUserAppService.Handle fail",
        stRet.ret,
        "req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  } else {
    XLOG_RUN(
        "FreezeUserAppService.Handle Succ|req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  }

  mmpayerrorapi::GetReporter().SetErrorcode(stRet.ret);
  uint64_t cost_time = cost.GetTimeDiffLong(true);
  //接口耗时上报
  ITF_COST_OSS_REPORT(cost_time, OSS_KEY_ITF_COST_FREEZEUSER);
  //接口请求上报
  ITF_REQ_OSS_REPORT(stRet.ret, OSS_KEY_ITF_REQ_FREEZEUSER);
  CLogReporter("mmpayddddemousersvr", __func__, stRet.ret, cost_time, req, resp);

  return stRet.ret;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::UnFreezeUser(
    const uint32_t head_uin,
    const mmpayddddemousersvr::UnFreezeUserReq& req,
    mmpayddddemousersvr::UnFreezeUserResp& resp) {
  MeshRet stRet;
  Comm::clsRuntimeLog cost;
  cost.Start();

  std::string req_debug_string = mmpaylog::utils::FilterPrivacy4PbMsg(req).ShortDebugString();
  XLOG_RUN("UnFreezeUser Begin|Req=%s", req_debug_string.c_str());

  Require require = Require("1", "UserRequireMapping", "UnFreezeUser", UserDTO(req.account_id()));
  Response response = RequireInterceptor::GetInstance()->Commit(require);
  if (response.exception != nullptr) {
    stRet.ret = -1000;
    resp.set_retmsg(response.exception->getMessage());
  }

  if (0 != stRet.ret) {
    XLOG_ERR(
        "UnFreezeUserAppService.Handle fail",
        stRet.ret,
        "req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  } else {
    XLOG_RUN(
        "UnFreezeUserAppService.Handle Succ|req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  }

  mmpayerrorapi::GetReporter().SetErrorcode(stRet.ret);
  uint64_t cost_time = cost.GetTimeDiffLong(true);
  //接口耗时上报
  ITF_COST_OSS_REPORT(cost_time, OSS_KEY_ITF_COST_UNFREEZEUSER);
  //接口请求上报
  ITF_REQ_OSS_REPORT(stRet.ret, OSS_KEY_ITF_REQ_UNFREEZEUSER);
  CLogReporter("mmpayddddemousersvr", __func__, stRet.ret, cost_time, req, resp);

  return stRet.ret;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::IsFrozen(
    const uint32_t head_uin,
    const mmpayddddemousersvr::IsFrozenReq& req,
    mmpayddddemousersvr::IsFrozenResp& resp) {
  MeshRet stRet;
  Comm::clsRuntimeLog cost;
  cost.Start();

  std::string req_debug_string = mmpaylog::utils::FilterPrivacy4PbMsg(req).ShortDebugString();
  XLOG_RUN("IsFrozen Begin|Req=%s", req_debug_string.c_str());

  Require require = Require("1", "UserRequireMapping", "IsFrozen", UserDTO(req.account_id()));
  Response response = RequireInterceptor::GetInstance()->Commit(require);
  if (response.exception != nullptr) {
    stRet.ret = -1000;
    resp.set_retmsg(response.exception->getMessage());
  } else {
    resp.set_is_frozen(boost::any_cast<bool>(response.value));
  }

  if (0 != stRet.ret) {
    XLOG_ERR(
        "IsFrozenAppService.Handle fail",
        stRet.ret,
        "req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  } else {
    XLOG_RUN(
        "IsFrozenAppService.Handle Succ|req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  }

  mmpayerrorapi::GetReporter().SetErrorcode(stRet.ret);
  uint64_t cost_time = cost.GetTimeDiffLong(true);
  //接口耗时上报
  ITF_COST_OSS_REPORT(cost_time, OSS_KEY_ITF_COST_ISFROZEN);
  //接口请求上报
  ITF_REQ_OSS_REPORT(stRet.ret, OSS_KEY_ITF_REQ_ISFROZEN);
  CLogReporter("mmpayddddemousersvr", __func__, stRet.ret, cost_time, req, resp);

  return stRet.ret;
}

int MMPayDDDDemoUserSvrServiceImpl_PB::GetUser(
    const uint32_t head_uin,
    const mmpayddddemousersvr::GetUserReq& req,
    mmpayddddemousersvr::GetUserResp& resp) {
  MeshRet stRet;
  Comm::clsRuntimeLog cost;
  cost.Start();

  std::string req_debug_string = mmpaylog::utils::FilterPrivacy4PbMsg(req).ShortDebugString();
  XLOG_RUN("GetUser Begin|Req=%s", req_debug_string.c_str());

  Require require =
      Require(std::to_string(rand()), "UserRequireMapping", "GetUser", UserDTO(req.account_id()));
  Response response = RequireInterceptor::GetInstance()->Commit(require);
  if (response.exception != nullptr) {
    stRet.ret = -1000;
    resp.set_retmsg(response.exception->getMessage());
  } else {
    boost::optional<UserDTO> user_optional =
        boost::any_cast<boost::optional<UserDTO>>(response.value);
    if (user_optional.has_value()) {
      resp.mutable_user_dto()->set_account_id(user_optional.value().account_id_);
      resp.mutable_user_dto()->set_is_frozen(user_optional.value().is_frozen_);
    } else {
      stRet.ret = -1001;
      resp.set_retmsg("查询为空");
    }
  }

  if (0 != stRet.ret) {
    XLOG_ERR(
        "GetUserAppService.Handle fail",
        stRet.ret,
        "req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  } else {
    XLOG_RUN(
        "GetUserAppService.Handle Succ|req.pkg: %s | resp.pkg: %s",
        req_debug_string.c_str(),
        mmpaylog::utils::FilterPrivacy4PbMsg(resp).ShortDebugString().c_str());
  }

  mmpayerrorapi::GetReporter().SetErrorcode(stRet.ret);
  uint64_t cost_time = cost.GetTimeDiffLong(true);
  //接口耗时上报
  ITF_COST_OSS_REPORT(cost_time, OSS_KEY_ITF_COST_GETUSER);
  //接口请求上报
  ITF_REQ_OSS_REPORT(stRet.ret, OSS_KEY_ITF_REQ_GETUSER);
  CLogReporter("mmpayddddemousersvr", __func__, stRet.ret, cost_time, req, resp);

  return stRet.ret;
}

/* clang-format off */
//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-service-cpp-member][自定义方法] // NOLINT
/* clang-format on */
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************

// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
/* clang-format off */
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-service-cpp-member][自定义方法] // NOLINT
/* clang-format on */
