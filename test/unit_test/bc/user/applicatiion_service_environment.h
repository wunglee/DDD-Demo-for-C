#ifndef TRANSFER_ApplicationServiceEnvironment_H
#define TRANSFER_ApplicationServiceEnvironment_H
#include "gtest/gtest.h"

#include "../../../../src/bc/user/application/user_service.h"
#include "../../../../src/global_business_dependency/service_interfaces/user/user_service_interface.h"
#include "user_query_mock.h"
#include "user_repository_mock.h"
class ApplicationServiceEnvironment : public ::testing::Test {
 public:
  std::vector<User> users;
  UserRepositoryMock* userRepositoryMock = nullptr;
  UserQueryMock* userQueryMock = nullptr;
  virtual void SetUp() {
    userRepositoryMock = UserRepositoryMock::BuildInstance(users);
    userQueryMock = UserQueryMock::BuildInstance(users);
    UserService::BuildInstance(userRepositoryMock, userQueryMock);
  }
  virtual void TearDown() {
    delete userRepositoryMock;
    delete userQueryMock;
    UserService::DestroyInstance();
  }
};

#endif  // TRANSFER_ApplicationServiceEnvironment_H
