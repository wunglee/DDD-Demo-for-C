#ifndef TRANSFER_公共测试方法_H
#define TRANSFER_公共测试方法_H
void 创建用户(UserServiceInterface * 用户服务接口_, std::string 付款方, bool 冻结付款方, std::string 收款方, bool 冻结收款方){
    用户服务接口_->添加用户(付款方);
    用户服务接口_->添加用户(收款方);
    if(冻结付款方)
        用户服务接口_->冻结用户(付款方);
    if(冻结收款方)
        用户服务接口_->冻结用户(收款方);
}
void 创建用户(UserServiceInterface * 用户服务接口_, std::string 付款方, std::string 收款方){
    创建用户(用户服务接口_,付款方,false,收款方,false);
}
void 初始化资金帐户(UserServiceInterface * 用户服务接口_){
    PublishSubscribeService::构建单例()->订阅("用户已创建", "FundEventMapping");
    创建用户(用户服务接口_,std::string("XX"),std::string("YY"));
}
void 检查转账状态(int 单号, Transfer::状态 状态_){
    boost::optional<Transfer> 转账_ = TransferService::获取单例()->获取转账(单号);
    ASSERT_EQ(转账_.has_value(),true);
    ASSERT_EQ(转账_.value().获取状态(),状态_);
}
int 申请转账(UserServiceInterface * 用户服务接口_, std::string 付款方, std::string 收款方, float 金额){
    创建用户(用户服务接口_,付款方,收款方);
    TransferServiceInterface* 转账服务_= NamingServiceManager::获取单例()->查找服务<TransferServiceInterface *>("TransferService").value();
    return 转账服务_->申请转账(付款方,收款方, 金额);
}
#endif //TRANSFER_公共测试方法_H
