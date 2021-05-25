#include "gtest/gtest.h"
#include "FundFrontendEnvironment.h"
#include "FundBackendEnvironment.h"
#include "ApplicationServiceEnvironment.h"
#include "../../../src/FundBC/BackendAdapters/FundDAO.h"
TEST_F(FundFrontendEnvironment, 转账已创建){
    PublishSubscribeService::构建单例()->发布(DomainEvent("转账已创建", 0,
                                                    转账已创建DTO(0, "XX", 1)));
    ASSERT_EQ(资金帐户服务模拟_->已经扣减资金,true);
}
TEST_F(FundFrontendEnvironment, 已添加资金帐户){
    PublishSubscribeService::构建单例()->发布(DomainEvent("用户已创建", 0, 用户已创建DTO("XX")));
    ASSERT_EQ(资金帐户服务模拟_->已添加资金帐户,true);
}
TEST_F(FundFrontendEnvironment, 已经到账){
    PublishSubscribeService::构建单例()->发布(DomainEvent("转账已出账", 0,
                                                    转账已出账DTO(0, "YY", 1)));
    ASSERT_EQ(资金帐户服务模拟_->已经到账,true);
}
TEST_F(FundFrontendEnvironment, 已经退款){
    PublishSubscribeService::构建单例()->发布(DomainEvent("转账退款中", 0,
                                                    转账退款事件(0, "XX", 1)));
    ASSERT_EQ(资金帐户服务模拟_->已经退款,true);
}
Fund 创建资金帐户(std::string 账号){
    Fund 资金帐户_(账号);
    FundRepository::获取单例()->新增资金帐户(资金帐户_);
    return 资金帐户_;
}
TEST_F(FundBackendEnvironment, 新增资金帐户){
    创建资金帐户("XX");
    ASSERT_EQ(FundQuery::获取单例()->获取资金帐户("XX")->获取账号(), "XX");
}
TEST_F(FundBackendEnvironment, 更新资金帐户){
    std::string 账号="XX";
    创建资金帐户(账号);
    Fund 资金帐户_ = Fund(账号, false, false, 5);
    FundRepository::获取单例()->更新资金帐户(资金帐户_);
    ASSERT_EQ(FundQuery::获取单例()->获取资金帐户(账号)->获取金额(), 5);
}
TEST_F(ApplicationServiceEnvironment, 添加资金帐户){
    FundService::获取单例()->添加资金帐户("XX");
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX").has_value(), true);
}
TEST_F(ApplicationServiceEnvironment, 初始化资金){
    FundService::获取单例()->添加资金帐户("XX");
    FundService::获取单例()->初始化资金("XX", 10);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->获取金额(), 10);
}
void 初始化资金(std::string 账号,float 金额){
    FundService::获取单例()->添加资金帐户(账号);
    FundService::获取单例()->初始化资金(账号, 金额);
}
TEST_F(ApplicationServiceEnvironment, 增加资金){
    初始化资金("XX",10);
    FundService::获取单例()->增加资金(1, "XX", 10);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->获取金额(), 20);
}
TEST_F(ApplicationServiceEnvironment, 扣减资金){
    初始化资金("XX",10);
    FundService::获取单例()->扣减资金(1, "XX", 3);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->获取金额(), 7);
}
TEST_F(ApplicationServiceEnvironment, 设置禁止付款){
    FundService::获取单例()->添加资金帐户("XX");
    FundService::获取单例()->设置禁止付款("XX", true);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->是否禁止转出(), true);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->是否禁止转入(), false);
}
TEST_F(ApplicationServiceEnvironment, 禁止付款){
    初始化资金("XX",10);
    FundService::获取单例()->设置禁止付款("XX", true);
    FundService::获取单例()->扣减资金(1, "XX", 3);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->获取金额(), 10);
}
TEST_F(ApplicationServiceEnvironment, 设置禁止收款){
    FundService::获取单例()->添加资金帐户("XX");
    FundService::获取单例()->设置禁止收款("XX", true);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->是否禁止转入(), true);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->是否禁止转出(), false);
}
TEST_F(ApplicationServiceEnvironment, 禁止收款) {
    FundService::获取单例()->添加资金帐户("XX");
    FundService::获取单例()->初始化资金("XX", 10);
    FundService::获取单例()->设置禁止收款("XX", true);
    FundService::获取单例()->增加资金(1, "XX", 3);
    ASSERT_EQ(FundService::获取单例()->获取资金帐户("XX")->获取金额(), 10);
}
void 增加资金帐户PO(FundPO &资金帐户PO_){
    FundDAO* 资金帐户DAO_=FundDAO::构建单例();
    资金帐户DAO_->新增资金帐户PO(资金帐户PO_);
}
void 验证资金帐户PO成功(FundPO &资金帐户PO_){
    boost::optional<FundPO> 结果=FundDAO::构建单例()->获取资金帐户PO(资金帐户PO_.账号);
    ASSERT_EQ(结果.has_value(), true);
    ASSERT_EQ(结果.value().账号, 资金帐户PO_.账号);
    ASSERT_EQ(结果.value().禁止转入_, 资金帐户PO_.禁止转入_);
    ASSERT_EQ(结果.value().禁止转出_, 资金帐户PO_.禁止转出_);
    ASSERT_EQ(结果.value().金额_, 资金帐户PO_.金额_);
}
void 验证资金帐户PO失败(FundPO &资金帐户PO_){
    boost::optional<FundPO> 结果=FundDAO::构建单例()->获取资金帐户PO(资金帐户PO_.账号);
    ASSERT_EQ(结果.has_value(), false);
}
TEST(DAO测试,增加){
    FundPO 资金帐户PO_("XX", false, false, 10);
    增加资金帐户PO(资金帐户PO_);
    验证资金帐户PO成功(资金帐户PO_);
}
TEST(DAO测试,更改){
    FundPO 资金帐户PO_1("XX", false, false, 10);
    增加资金帐户PO(资金帐户PO_1);
    FundPO 资金帐户PO_2("YY", true, true, 20);
    FundDAO::构建单例()->更新资金帐户PO(资金帐户PO_2);
    验证资金帐户PO失败(资金帐户PO_2);
    FundPO 资金帐户PO_3("XX", true, true, 20);
    FundDAO::构建单例()->更新资金帐户PO(资金帐户PO_3);
    验证资金帐户PO成功(资金帐户PO_3);
}