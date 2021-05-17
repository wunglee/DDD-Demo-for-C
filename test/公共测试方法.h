#ifndef TRANSFER_公共测试方法_H
#define TRANSFER_公共测试方法_H
void 创建用户(std::string 付款方,bool 冻结付款方,std::string 收款方,bool 冻结收款方){
    用户服务接口* 用户服务_= 命名服务管理器::获取单例()->查找服务<用户服务接口 *>("用户服务").value();
    用户服务_->添加用户(付款方);
    用户服务_->添加用户(收款方);
    if(冻结付款方)
        用户服务_->冻结用户(付款方);
    if(冻结收款方)
        用户服务_->冻结用户(收款方);
}
void 创建用户(std::string 付款方,std::string 收款方){
    创建用户(付款方,false,收款方,false);
}
void 检查转账状态(int 单号, 转账::状态 状态_){
    转账服务接口* 转账服务_= 命名服务管理器::获取单例()->查找服务<转账服务接口 *>("转账服务").value();
    boost::optional<转账> 转账_ = 转账服务_->获取转账(单号);
    ASSERT_EQ(转账_.has_value(),true);
    ASSERT_EQ(转账_.value().获取状态(),状态_);
}
int 申请转账(std::string 付款方,std::string 收款方,float 金额){
    创建用户(付款方,收款方);
    转账服务接口* 转账服务_= 命名服务管理器::获取单例()->查找服务<转账服务接口 *>("转账服务").value();
    return 转账服务_->申请转账(付款方,收款方, 金额);
}
#endif //TRANSFER_公共测试方法_H
