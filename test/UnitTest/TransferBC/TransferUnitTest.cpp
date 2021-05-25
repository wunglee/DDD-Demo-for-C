#include "gtest/gtest.h"
#include "ApplicationTestEnvironment.h"
#include "TransferEventEnvironment.h"
#include "TransferBackendEnvironment.h"
#include "../../CommonTestFuntions.h"
#include "../../../src/TransferBC/BackendAdapters/TransferDAO.h"
#include "../../../src/TransferBC/FrontendAdapters/ProtobufRequireAdaptor.h"
#include "TransferFrontendEnvironment.h"

int 创建转账(std::string 付款方, std::string 收款方, float 金额, Transfer::状态 状态){
    Transfer 转账_=Transfer::构造旧的转账(rand(), TransferUser(付款方), TransferUser(收款方), 金额, 状态);
    TransferRepositoryMock::获取已存在的单例()->新增转账(转账_);
    return 转账_.获取单号();
}
TEST_F(Application测试环境, 申请转账){
    检查转账状态(申请转账(用户服务模拟_,"XX","YY",100), Transfer::已创建);
}
void 测试帐户冻结时申请转账(UserServiceInterface * 用户服务模拟_, bool 冻结付款方, bool 冻结收款方){
    创建用户(用户服务模拟_,"XX",冻结付款方,"YY",冻结收款方);
    TransferServiceInterface* 转账服务_= NamingServiceManager::获取单例()->查找服务<TransferServiceInterface *>("TransferService").value();
    ASSERT_THROW(转账服务_->申请转账("XX", "YY",100), Exception);
}
TEST_F(Application测试环境, 付款用户冻结时申请转账){
    测试帐户冻结时申请转账(用户服务模拟_,true,false);
}
TEST_F(Application测试环境, 收款用户冻结时申请转账){
    测试帐户冻结时申请转账(用户服务模拟_,false,true);
}
TransferServiceInterface* 获取转账请求服务(){
    return NamingServiceManager::获取单例()->查找服务<TransferServiceInterface *>("TransferService").value();
}
int 初始化转账(Transfer::状态 状态){
    return 创建转账("XX","YY",100,状态);
}
TEST_F(Application测试环境, 通知已出账){
    int 单号=初始化转账(Transfer::已创建);
    获取转账请求服务()->通知出账(单号);
    检查转账状态(单号, Transfer::已出账);
}
TEST_F(Application测试环境, 通知已取消){
    int 单号=初始化转账(Transfer::已创建);
    获取转账请求服务()->通知取消(单号, Exception(""));
    检查转账状态(单号, Transfer::已取消);
}
TEST_F(Application测试环境, 通知已到账){
    int 单号=初始化转账(Transfer::已出账);
    获取转账请求服务()->通知到账(单号,"YY");
    检查转账状态(单号, Transfer::已到账);
}
TEST_F(Application测试环境, 资金出账后账号被冻结){
    创建用户(用户服务模拟_,"XX","YY");
    int 单号=初始化转账(Transfer::已出账);
    用户服务模拟_->冻结用户("YY");
    ASSERT_THROW(获取转账请求服务()->通知到账(单号,"YY"), Exception);
}
TEST_F(Application测试环境, 通知申请退款){
    int 单号=初始化转账(Transfer::Transfer::已出账);
    获取转账请求服务()->通知申请退款(单号, Exception(""));
    检查转账状态(单号, Transfer::退款中);
}
TEST_F(Application测试环境, 完成退款){
    int 单号=初始化转账(Transfer::Transfer::退款中);
    获取转账请求服务()->通知到账(单号,"XX");
    检查转账状态(单号, Transfer::已退回);
}
TEST_F(TransferEventEnvironment, 通知取消已调用){
    PublishSubscribeService::构建单例()->发布(DomainEvent("扣减已失败", 0, Exception("")));
    ASSERT_EQ(TansferServiceMock::获取单例()->通知取消已调用, true);
}
TEST_F(TransferEventEnvironment, 通知出账已调用){
    PublishSubscribeService::构建单例()->发布(DomainEvent("扣减已成功", 0, ""));
    ASSERT_EQ(TansferServiceMock::获取单例()->通知出账已调用, true);
}
TEST_F(TransferEventEnvironment, 通知到账已调用){
    PublishSubscribeService::构建单例()->发布(DomainEvent("增资已成功", 0, 增资已成功DTO(0, "YY", 1)));
    ASSERT_EQ(TansferServiceMock::获取单例()->通知到账已调用, true);
}
TEST_F(TransferEventEnvironment, 通知申请退款已调用){
    PublishSubscribeService::构建单例()->发布(DomainEvent("增资已失败", 0, Exception("")));
    ASSERT_EQ(TansferServiceMock::获取单例()->通知申请退款已调用, true);
}
TEST_F(TransferEventEnvironment, 通知退款已调用){
    PublishSubscribeService::构建单例()->发布(DomainEvent("增资已成功", 0, 增资已成功DTO(0, "XX", 1)));
    ASSERT_EQ(TansferServiceMock::获取单例()->通知退款已调用, true);
}
int 仓储新增转账(std::string 转账方,std::string 收款方,float 金额) {
    TransferRepository *转账仓储_ = TransferRepository::获取单例();
    Transfer 转账_ = Transfer::构造新的转账(
            TransferUser(转账方, false),
            TransferUser(收款方, false),
            金额);
    转账仓储_->新增转账(转账_);
    return 转账_.获取单号();
}
TEST_F(从适配器层转账仓储测试环境, 仓储新增转账){
    int 单号=仓储新增转账("XX","YY",10);
    ASSERT_EQ(TransferRepository::获取单例()->获取必须存在的转账(单号).获取状态(), Transfer::已创建);
}
TEST_F(从适配器层转账仓储测试环境, 仓储更新转账状态){
    int 单号=仓储新增转账("XX","YY",10);
    TransferRepository::获取单例()->更新转账状态(单号, Transfer::已出账);
    ASSERT_EQ(TransferRepository::获取单例()->获取必须存在的转账(单号).获取状态(), Transfer::已出账);
}
int DAO新增转账PO(int 单号,std::string 转账方,std::string 收款方,float 金额,int 状态){
    TransferDAO* 转账DAO_= TransferDAO::构建单例();
    TransferPO 转账PO_(单号, 转账方, 收款方, 状态, 金额);
    转账DAO_->新增转账PO(转账PO_);
    return 转账PO_.单号;
}
TEST(从适配器层转账DAO测试, 新增){
    int 单号=DAO新增转账PO(1,"XX","YY",10,0);
    TransferDAO* 转账DAO_= TransferDAO::构建单例();
    ASSERT_EQ(转账DAO_->获取转账PO(单号)->状态,0);
}
TEST(从适配器层转账DAO测试,更新转账PO状态){
    int 单号=DAO新增转账PO(1,"XX","YY",10,0);
    TransferDAO* 转账DAO_= TransferDAO::构建单例();
    转账DAO_->更新转账PO状态(单号,2);
    ASSERT_EQ(转账DAO_->获取转账PO(单号)->状态,2);
}
TEST_F(TransferFrontendEnvironment, 处理转账请求){
    ProtobufRequireAdaptor * PB请求适配器_= NamingServiceManager::获取单例()->查找服务<ProtobufRequireAdaptor *>("ProtobufRequireAdaptor").value();
    PB请求适配器_->请求请求("");
}

