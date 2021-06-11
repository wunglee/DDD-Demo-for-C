// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1
#include "mmpay_git/mmpay_comm/component_export/mmpaylogapi/export_include/mmpaylog_api.h"

#include "mmpayddddemousersvrserver.h"

using namespace Comm;

int main(int argc, char** argv) {
  const char* pszCfg = mmpaylogapi::GetOpt(argc, argv, "-i", "");
  PLOG_INIT_4_SK("mmpayddddemousersvr", pszCfg);

  MMPayDDDDemoUserSvrServer server(argc, argv);
  server.Run();
  return 0;
}
