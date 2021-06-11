// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1

#include "iSvrkit.h"
#include "mmpayddddemousersvrclient.h"
#include "mmpayddddemousersvrtestimpl_pb.h"

using namespace Comm;

MMPayDDDDemoUserSvrTestSuite_PBImpl::MMPayDDDDemoUserSvrTestSuite_PBImpl() {}

MMPayDDDDemoUserSvrTestSuite_PBImpl::~MMPayDDDDemoUserSvrTestSuite_PBImpl() {
  printf(
      "\033[41;37m\n  <<<<<< "
      "警告：通过本工具获取的信息为敏感信息，请不要滥用本工具，不要触犯高压线！"
      ">>>>>>\n\n\n\33[0m");
}

int MMPayDDDDemoUserSvrTestSuite_PBImpl::SKEcho(Comm::SKOptMap* opt_map) {
  const char* str = opt_map->Get('s');
  unsigned int uin = 0;
  int ret = opt_map->GetUInt('u', &uin);

  if (NULL == str || ret != 0 || uin < 10000) {
    return -1;
  }

  char resp[256] = {0};
  int len = sizeof(resp);

  MMPayDDDDemoUserSvrClient client;
  ret = client.SKEcho(uin, str, resp, &len);

  printf("SKEcho %d\n", ret);
  printf("str %s, resp [%s], len %d\n", str, resp, len);
  return 0;
}
