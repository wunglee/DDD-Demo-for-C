#ifndef TRANSFER_命令队列_H
#define TRANSFER_命令队列_H
#include "命令.h"
#include <queue>
class 命令队列 {
private:
    std::queue<命令> 命令队列_;
public:
    ~命令队列(){
        std::queue<命令> 空队列;
        swap(空队列, 命令队列_);
    }
    void 加入命令(命令& 命令){
        命令队列_.push(命令);
    }
    int 队列大小(){
        return 命令队列_.size();
    }
    boost::optional<命令> 取出命令(){
        if(!命令队列_.empty()){
            命令 命令_ = 命令队列_.front();
            命令队列_.pop();
            return 命令_;
        }
        return boost::none;
    }
};


#endif //TRANSFER_消息队列_H
