#include "../../../../src/bc/user/backend_adapters/user_menory_dao.h"
#include "applicatiion_service_environment.h"
#include "user_backend_environment.h"
#include "user_frontend_environment.h"
#include "gtest/gtest.h"

TEST_F(ApplicationServiceEnvironment, AddUser) {
  UserService::GetInstance()->AddUser("XX");
  ASSERT_EQ(UserService::GetInstance()->GetUser("XX").has_value(), true);
}
void freeze_user_test() {
  UserService::GetInstance()->AddUser("XX");
  UserService::GetInstance()->FreezeUser("XX");
  ASSERT_EQ(UserService::GetInstance()->GetUser("XX")->is_frozen_, true);
}
TEST_F(ApplicationServiceEnvironment, freeze_user) { freeze_user_test(); }
TEST_F(ApplicationServiceEnvironment, unfreeze_user) {
  freeze_user_test();
  UserService::GetInstance()->UnfreezeUser("XX");
  ASSERT_EQ(UserService::GetInstance()->GetUser("XX")->is_frozen_, false);
}
TEST_F(UserBackendEnvironment, AddUser) {
  UserRepository::GetInstance()->AddUser("XX");
  ASSERT_EQ(UserQuery::GetInstance()->GetUser("XX").has_value(), true);
}
TEST(DAOTEST, GetUserPO) {
  UserMenoryDAO::BuildInstance()->AddUserPO(UserPO("XX"));
  ASSERT_EQ(UserMenoryDAO::BuildInstance()->GetUserPO("XX").has_value(), true);
}
TEST(DAOTEST, UpdateUserPO) {
  UserMenoryDAO::BuildInstance()->AddUserPO(UserPO("XX"));
  UserMenoryDAO::BuildInstance()->UpdateUserPO(UserPO("XX", true));
  ASSERT_EQ(UserMenoryDAO::BuildInstance()->GetUserPO("XX")->frozen_, true);
}

TEST_F(UserFrontendEnvironment, add_user_from_httpService) {
  HttpRequest httpRequest("", std::string("XX"));
  UserHttpService::GetInstance()->AddUser(httpRequest);
  ASSERT_EQ(UserServiceMock::GetInstance()->GetUser("XX").has_value(), true);
}
TEST_F(UserFrontendEnvironment, get_user_from_httpService) {
  HttpRequest httpRequest("", std::string("XX"));
  UserHttpService::GetInstance()->AddUser(httpRequest);
  boost::any result = UserHttpService::GetInstance()->GetUser(httpRequest).body;
  ASSERT_EQ(result.empty(), false);
  ASSERT_EQ(boost::any_cast<UserDTO>(result).account_id_, "XX");
}
TEST_F(UserFrontendEnvironment, freeze_user_from_httpService) {
  HttpRequest httpRequest("", std::string("XX"));
  UserHttpService::GetInstance()->AddUser(httpRequest);
  UserHttpService::GetInstance()->FreezeUser(httpRequest);
  ASSERT_EQ(UserServiceMock::GetInstance()->GetUser("XX")->is_frozen_, true);
}
TEST_F(UserFrontendEnvironment, unfreeze_user_from_httpService) {
  HttpRequest httpRequest("", std::string("XX"));
  UserHttpService::GetInstance()->AddUser(httpRequest);
  UserHttpService::GetInstance()->FreezeUser(httpRequest);
  UserHttpService::GetInstance()->UnfreezeUser(httpRequest);
  ASSERT_EQ(UserServiceMock::GetInstance()->GetUser("XX")->is_frozen_, false);
}
TEST_F(UserFrontendEnvironment, get_user_is_frozen_from_httpService) {
  HttpRequest httpRequest("", std::string("XX"));
  UserHttpService::GetInstance()->AddUser(httpRequest);
  UserHttpService::GetInstance()->FreezeUser(httpRequest);
  boost::any result =
      UserHttpService::GetInstance()->IsFrozen(httpRequest).body;
  ASSERT_EQ(boost::any_cast<bool>(result), true);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}