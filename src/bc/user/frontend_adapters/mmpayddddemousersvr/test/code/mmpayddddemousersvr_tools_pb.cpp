// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <getopt.h>
#include <unistd.h>

#include "iLog.h"
#include "iSvrkit.h"
#include "mmpayddddemousersvrclient.h"
#include "mmpayddddemousersvrtestimpl_pb.h"
#include "sk_mmpayddddemousersvrtest.pb.h"
#include "skjsonutils.h"

using namespace Comm;

void showUsage(const char* program) {
  printf(
      "\nUsage: %s [-c <config>] [-f <func>] [-Z <idc name>] [-T <oa ticket>] "
      "[-v] [--json <json file>] [--help <json file>]\n",
      program);

  MMPayDDDDemoUserSvrTestSuite_PB::Name2Func_t* name2func =
      MMPayDDDDemoUserSvrTestSuite_PB::GetName2Func();

  for (int i = 0;; i++) {
    MMPayDDDDemoUserSvrTestSuite_PB::Name2Func_t* iter = &(name2func[i]);

    if (NULL == iter->sName) break;

    printf("\t-f %s %s\n", iter->sName, iter->sUsage);
  }

  printf("\n");
  exit(0);
}

int main(int argc, char* argv[]) {
  const char* func = NULL;
  const char* config = NULL;

  for (int i = 1; i < argc - 1; i++) {
    if (0 == strcmp(argv[i], "-c")) {
      config = argv[++i];
    }
    if (0 == strcmp(argv[i], "-f")) {
      func = argv[++i];
    }
    if (0 == strcmp(argv[i], "-v")) {
      showUsage(argv[0]);
    }
  }

  if (NULL == func) {
    showUsage(argv[0]);
  }

  if (NULL != config) {
    MMPayDDDDemoUserSvrClientConfig::GetDefault()->SetFileIfUnset(config);
  }

  Comm::OpenLog("MMPayDDDDemoUserSvr", 3, "/home/qspace/log");

  MMPayDDDDemoUserSvrTestSuite_PB::Name2Func_t* target = NULL;
  MMPayDDDDemoUserSvrTestSuite_PB::Name2Func_t* name2func =
      MMPayDDDDemoUserSvrTestSuite_PB::GetName2Func();

  for (int i = 0; i < 100; i++) {
    MMPayDDDDemoUserSvrTestSuite_PB::Name2Func_t* iter = &(name2func[i]);

    if (NULL == iter->sName) {
      break;
    }

    if (0 == strcasecmp(func, iter->sName)) {
      target = iter;
      break;
    }
  }

  if (NULL == target) showUsage(argv[0]);

  Comm::SKOptMap optMap(target->sOptString);

  static const int OPT_HELP = 1001;
  ::option long_opts[] = {{"json", required_argument, 0, OPT_JSON},
                          {"help", required_argument, 0, OPT_HELP},
                          {0, 0, 0, 0}};

  if (0 != optMap.Parse(argc, argv, long_opts)) showUsage(argv[0]);

  const char* output_file_path = optMap.Get(OPT_HELP);
  if (output_file_path != NULL) {
    return GenerateReqDesc(mmpayddddemousersvr::MMPayDDDDemoUserSvr::descriptor(), func,
                           output_file_path);
  }

  MMPayDDDDemoUserSvrTestSuite_PB::TestFunc_t testfunc = target->tFunc;
  MMPayDDDDemoUserSvrTestSuite_PBImpl testSuite;

  if (0 != (testSuite.*testfunc)(&optMap)) showUsage(argv[0]);

  return 0;
}
