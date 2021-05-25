#ifndef TRANSFER_用户事件处理器_H
#define TRANSFER_用户事件处理器_H
#include "../../框架组件/事件发布订阅/事件监听器.h"
//从事件队列中取出事件进行处理
class 用户事件处理器 : public 事件监听器 {
private:
    static 用户事件处理器 *用户事件处理器_;
    用户事件处理器() {}
public:
    ~用户事件处理器() {
        用户事件处理器::用户事件处理器_ = nullptr;
    }
    static 用户事件处理器 *构建单例() {
        if (用户事件处理器_ == nullptr) {
            用户事件处理器_ = new 用户事件处理器();
        }
        return 用户事件处理器_;
    }
    void 处理(const 领域事件 领域事件_){
    }
};


#endif //TRANSFER_用户事件处理器_H
