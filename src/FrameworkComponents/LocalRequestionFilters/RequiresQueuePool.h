#ifndef TRANSFER_请求队列池_H
#define TRANSFER_请求队列池_H
#include "vector"
#include "RequiresQueue.h"
#include "RequiresQueuePoolInterface.h"
class RequiresQueuePool : public RequiresQueuePoolInterface {
private:
    std::list<RequiresQueue> 队列池_;
    static RequiresQueuePool * 请求队列池_;
    RequiresQueuePool(int 大小=10){
        for(int i=0;i<大小;i++){
            队列池_.push_back(RequiresQueue());
        }
    }
public:
    virtual ~RequiresQueuePool(){
        队列池_.clear();
        RequiresQueuePool::请求队列池_= nullptr;
    }
    static RequiresQueuePool* 构建单例(int 大小=10){
        if(RequiresQueuePool::请求队列池_ == nullptr){
            RequiresQueuePool::请求队列池_=new RequiresQueuePool(大小);
        }
        return RequiresQueuePool::请求队列池_;
    }
    static RequiresQueuePool* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(RequiresQueuePool::请求队列池_ != nullptr)
            delete RequiresQueuePool::请求队列池_;
    }
    void 加入请求(Require& 请求) {
        boost::optional<RequiresQueue&> 请求队列_= 选择最小队列();
        if(请求队列_.has_value()){
            请求队列_.value().加入请求(请求);
        }
    }
    boost::optional<Require>  取出请求() {
        boost::optional<RequiresQueue&> 请求队列_= 选择最大队列();
        if(请求队列_.has_value()){
            return 请求队列_.value().取出请求();
        }
        return boost::none;
    }
    boost::optional<RequiresQueue&> 选择最小队列(){
        long 最小值=std::numeric_limits<long>::max();
        RequiresQueue* 选择的请求队列= nullptr;
        for(RequiresQueue& 请求队列_:队列池_){
            int 当前大小=请求队列_.队列大小();
            if(当前大小<最小值){
                最小值=当前大小;
                选择的请求队列=&请求队列_;
                if(最小值==0) break;
            }
        }
        return *选择的请求队列;
    }
    boost::optional<RequiresQueue&> 选择最大队列(){
        long 最大值=0;
        RequiresQueue* 选择的请求队列= nullptr;
        for(RequiresQueue& 请求队列_:队列池_){
            int 当前大小=请求队列_.队列大小();
            if(当前大小>最大值){
                最大值=当前大小;
                选择的请求队列=&请求队列_;
            }
        }
        return *选择的请求队列;
    }
};


#endif //TRANSFER_请求队列池_H
