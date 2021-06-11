//
// Created by 王立 on 2021/5/24.
//
#pragma once
#include <string>

#include "network_protocol/http.h"

class UserHttpServiceInterface {
 public:
  virtual ~UserHttpServiceInterface() {}
  virtual HttpResponse GetUser(HttpRequest& request) = 0;

  virtual HttpResponse IsFrozen(HttpRequest& request) = 0;

  virtual HttpResponse AddUser(HttpRequest& request) = 0;

  virtual HttpResponse FreezeUser(HttpRequest& request) = 0;

  virtual HttpResponse UnFreezeUser(HttpRequest& request) = 0;
};
