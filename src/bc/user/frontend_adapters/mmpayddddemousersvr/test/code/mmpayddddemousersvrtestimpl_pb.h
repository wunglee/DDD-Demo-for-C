// 瓦特任务ID：f48cbd20-c43f-11eb-bc64-1d35e522ece7
// 瓦特任务版本：1
#pragma once

#include <stdio.h>

#include "sk_mmpayddddemousersvrtest.pb.h"

namespace Comm {
class SKOptMap;
}

class MMPayDDDDemoUserSvrTestSuite_PBImpl : public MMPayDDDDemoUserSvrTestSuite_PB {
 public:
  MMPayDDDDemoUserSvrTestSuite_PBImpl();
  virtual ~MMPayDDDDemoUserSvrTestSuite_PBImpl();

  virtual int SKEcho(Comm::SKOptMap* opt_map);
};
