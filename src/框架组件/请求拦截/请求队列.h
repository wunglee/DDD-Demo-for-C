#ifndef TRANSFER_请求队列_H
#define TRANSFER_请求队列_H
#include "请求.h"
#include <queue>
class 请求队列 {
private:
    std::queue<请求> 请求队列_;
public:
    ~请求队列(){
        std::queue<请求> 空队列;
        swap(空队列, 请求队列_);
    }
    void 加入请求(请求& 请求){
        请求队列_.push(请求);
    }
    int 队列大小(){
        return 请求队列_.size();
    }
    boost::optional<请求> 取出请求(){
        if(!请求队列_.empty()){
            请求 请求_ = 请求队列_.front();
            请求队列_.pop();
            return 请求_;
        }
        return boost::none;
    }
};


#endif //TRANSFER_消息队列_H
