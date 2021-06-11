//
// Created by 王立 on 2021/6/7.
//

#ifndef DDD_DEMO_FOR_C_IDEMPOTENT_MANAGER_H
#define DDD_DEMO_FOR_C_IDEMPOTENT_MANAGER_H

#include <string>

class IdempotentManager {
 public:
  virtual void check_id(std::string id) {};
  virtual void save_id(std::string id) {};
};

#endif  // DDD_DEMO_FOR_C_IDEMPOTENT_MANAGER_H
