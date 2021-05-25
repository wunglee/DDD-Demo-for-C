#include "gtest/gtest.h"
#include "RequireFlowTestEnvironment.h"
#include "../CommonTestFuntions.h"


TEST_F(RequireFlowTestEnvironment, 创建用户以后创建资金帐户){
    boost::optional<Fund> 资金帐户1=FundServiceFactory::获取单例()->获取资金帐户("XX");
    boost::optional<Fund> 资金帐户2=FundServiceFactory::获取单例()->获取资金帐户("YY");
    ASSERT_EQ(资金帐户1.has_value(),true);
    ASSERT_EQ(资金帐户2.has_value(),true);
    ASSERT_EQ(资金帐户1.value().获取账号(),"XX");
    ASSERT_EQ(资金帐户2.value().获取账号(),"YY");
}
void 设置禁止收付款(bool 禁止付款, bool 禁止收款){
    if (禁止付款) {
        FundServiceFactory::获取单例()->设置禁止付款("XX", true);
    }
    if (禁止收款) {
        FundServiceFactory::获取单例()->设置禁止收款("YY", true);
    }
}
int 创建转账(float 付款帐户资金,float 付款金额) {
    FundServiceFactory::获取单例()->初始化资金("XX", 付款帐户资金);
    return TransferService::获取单例()->申请转账("XX", "YY", 付款金额);
}
TEST_F(RequireFlowTestEnvironment, 转账创建成功){
    检查转账状态(创建转账(1000,100), Transfer::已创建);
}

TEST_F(RequireFlowTestEnvironment, 禁止付款){
    PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("扣减已失败", "TransferEventMonitor");
    设置禁止收付款(true, false);
    检查转账状态(创建转账(1000,100), Transfer::已取消);
}
TEST_F(RequireFlowTestEnvironment, 余额不足){
    PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("扣减已失败", "TransferEventMonitor");
    检查转账状态(创建转账(100,1000), Transfer::已取消);
}
TEST_F(RequireFlowTestEnvironment, 转账出账成功){
    PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("扣减已成功", "TransferEventMonitor");
    检查转账状态(创建转账(1000,100), Transfer::已出账);
}
TEST_F(RequireFlowTestEnvironment, 禁止收款){
    PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("扣减已成功", "TransferEventMonitor");
    PublishSubscribeService::构建单例()->订阅("转账已出账", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("增资已失败", "TransferEventMonitor");
    设置禁止收付款(false, true);
    检查转账状态(创建转账(1000,100), Transfer::退款中);
}

TEST_F(RequireFlowTestEnvironment, 正常收款){
    PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("扣减已成功", "TransferEventMonitor");
    PublishSubscribeService::构建单例()->订阅("转账已出账", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("增资已成功", "TransferEventMonitor");
    检查转账状态(创建转账(1000,100), Transfer::已到账);
}
TEST_F(RequireFlowTestEnvironment, 正常退款){
    PublishSubscribeService::构建单例()->订阅("转账已创建", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("扣减已成功", "TransferEventMonitor");
    PublishSubscribeService::构建单例()->订阅("转账已出账", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("增资已失败", "TransferEventMonitor");
    PublishSubscribeService::构建单例()->订阅("转账退款中", "FundEventMapping");
    PublishSubscribeService::构建单例()->订阅("增资已成功", "TransferEventMonitor");
    设置禁止收付款(false, true);
    检查转账状态(创建转账(1000,100), Transfer::已退回);
}