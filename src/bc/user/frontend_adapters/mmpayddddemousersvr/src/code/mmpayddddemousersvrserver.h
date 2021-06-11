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

#include "iSvrkit.h"
#include "mmpay/mmpayxwatt/xwatt/log/logger.h"
#include "mmpay/mmpayxwatt/xwatt/mmdata/mmdata_reporter.h"
#include "mmpay_git/mmpay_comm/component_export/mmpaylogapi/export_include/mmpaylog_api.h"
#include "mmpayddddemousersvrconfig.h"
#include "mmpayddddemousersvrserviceimpl_pb.h"
#include "mmserver.h"
#include "sk_mmpayddddemousersvrdispatcher.pb.h"

//// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-server-header][自定义头文件] // NOLINT
// ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
#include "comm/dal_set/src/dal_set.h"
#include "comm/dal_set/src/dal_set_define.h"
#include "comm/dal_set/src/mysqlstorage.h"
#include "product/framework_configure.h"
#include "product/user_service_factory.h"
// ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
//// XWATT-TAG-END:[flow][mmpayddddemousersvr-server-header][自定义头文件] // NOLINT

class MMPayDDDDemoUserSvrServer : public Comm::MMServer<MMPayDDDDemoUserSvrConfig> {
 public:
  MMPayDDDDemoUserSvrServer(int argc, char** argv)
      : Comm::MMServer<MMPayDDDDemoUserSvrConfig>(argc, argv, "mmpayddddemousersvr") {}

  void SKServerProc(
      Comm::SKCtrlInfo_t* ctrl_info,
      Comm::SKBuffer* ctx,
      Comm::SKBuffer* in_pkg,
      Comm::SKBuffer* out_pkg,
      void* args) {
    MMPayDDDDemoUserSvrServiceImpl_PB service(GetConfig());
    MMPayDDDDemoUserSvrDispatcher_PB dispatcher(ctrl_info, ctx, in_pkg, out_pkg, &service);
    dispatcher.Dispatch();
  }

  virtual void BeforeMasterRun(void* pvProcArgs) {
    // 生成工具信息的上报
    auto oReport = xwatt::mmdata::CMMDataReporter();
    oReport.SetServerName("mmpayddddemousersvr");
    oReport.SetCodeCreateTime("2021-06-03 16:58:19");
    oReport.SetUserName("floatman");
    oReport.SetCodeVersion("b5f5627e");
    oReport.SetGeneratorVersion("v1.0.1");
    oReport.SetEventName("3");
    oReport.Report();

    /* clang-format off */
    //// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-server-BeforeMasterRun][BeforeMasterRun] // NOLINT
    // ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
      
    // ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
    //// XWATT-TAG-END:[flow][mmpayddddemousersvr-server-BeforeMasterRun][BeforeMasterRun] // NOLINT
    /* clang-format on */
  }

  /* clang-format off */
  //// XWATT-TAG-BEGIN:[flow][mmpayddddemousersvr-server-member][自定义方法] // NOLINT
  // ***********************  ↓↓↓↓ 可在以下区域添加自定义内容 ↓↓↓↓  ************************
  virtual void BeforeChildRun(void* pvProcArgs) {
    UserServiceFactory::RegistService();

    // 初始化DALSET
		CDAL_SET->SetServiceName("mmpayddddemousersvr"); // 设置服务模块名字
		CDAL_SET->AddDBRole("mmpay_ddd_demo"); // 添加要访问的 DB 角色
		CDAL_SET->SetConnTimeout(1);
		CDAL_SET->SetReadTimeout(1);
		CDAL_SET->SetWriteTimeout(1);
    dalset::OSSKeyMap mapOssKey;
		int retcode = CDAL_SET->Initialize(mapOssKey, 62); //初始化
		if (retcode != 0)
		{
			PLOG_ERR("CDAL_SET->Initialize ",
			          retcode, "init error:%s\n", CDAL_SET->getLastErrMsg());
			return;
		}

    dalset::IDBOperator* pDBOperator = CDAL_SET->GetDBOperator(0, 0, "mmpay_ddd_demo", "T_Idempotent", 0, false);
    if (pDBOperator == nullptr) {
      			printf("CDAL_SET->GetDBOperator error.\n");
			return;
    }

    std::shared_ptr<dalset::CMySqlStorage> storage = std::make_shared<dalset::CMySqlStorage>();
    storage->SetDBOperator(pDBOperator);
    FrameWorkConfigure::ConfigureFrameWork(storage);
  }

  virtual void AfterChildRun(void* pvProcArgs) {
  }
  // ***********************  ↑↑↑↑ 可在以上区域添加自定义内容 ↑↑↑↑  ************************
  //// XWATT-TAG-END:[flow][mmpayddddemousersvr-server-member][自定义方法] // NOLINT
  /* clang-format on */
};
