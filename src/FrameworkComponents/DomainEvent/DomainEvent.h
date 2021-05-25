#ifndef ARGS_领域事件_H
#define ARGS_领域事件_H
#include "../../TransferBC/Domain/Transfer.h"
#include "boost/any.hpp"
#include "../../UserBC/FrontendAdapters/UserDTO.h"
class DomainEvent {
public:
    DomainEvent(std::string 事件名, long 事务ID, boost::any 内容): 事件名_(事件名), 事务ID_(事务ID), 内容_(内容){}
    std::string 获取事件名() const {
        return 事件名_;
    }
    long 获取事务ID() const {
        return 事务ID_;
    }
    const boost::any 获取内容() const {
        return 内容_;
    }
private:
    long 事务ID_;
    boost::any 内容_;
    std::string 事件名_;
};
#endif //ARGS_领域事件_H
