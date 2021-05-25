#ifndef TRANSFER_请求队列池_H
#define TRANSFER_请求队列池_H
#include "vector"
#include "请求队列.h"
#include "请求队列池接口.h"
class 请求队列池 : public 请求队列池接口 {
private:
    std::list<请求队列> 队列池_;
    static 请求队列池 * 请求队列池_;
    请求队列池(int 大小=10){
        for(int i=0;i<大小;i++){
            队列池_.push_back(请求队列());
        }
    }
public:
    virtual ~请求队列池(){
        队列池_.clear();
        请求队列池::请求队列池_= nullptr;
    }
    static 请求队列池* 构建单例(int 大小=10){
        if(请求队列池::请求队列池_ == nullptr){
            请求队列池::请求队列池_=new 请求队列池(大小);
        }
        return 请求队列池::请求队列池_;
    }
    static 请求队列池* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(请求队列池::请求队列池_!= nullptr)
            delete 请求队列池::请求队列池_;
    }
    void 加入请求(请求& 请求) {
        boost::optional<请求队列&> 请求队列_= 选择最小队列();
        if(请求队列_.has_value()){
            请求队列_.value().加入请求(请求);
        }
    }
    boost::optional<请求>  取出请求() {
        boost::optional<请求队列&> 请求队列_= 选择最大队列();
        if(请求队列_.has_value()){
            return 请求队列_.value().取出请求();
        }
        return boost::none;
    }
    boost::optional<请求队列&> 选择最小队列(){
        long 最小值=std::numeric_limits<long>::max();
        请求队列* 选择的请求队列= nullptr;
        for(请求队列& 请求队列_:队列池_){
            int 当前大小=请求队列_.队列大小();
            if(当前大小<最小值){
                最小值=当前大小;
                选择的请求队列=&请求队列_;
                if(最小值==0) break;
            }
        }
        return *选择的请求队列;
    }
    boost::optional<请求队列&> 选择最大队列(){
        long 最大值=0;
        请求队列* 选择的请求队列= nullptr;
        for(请求队列& 请求队列_:队列池_){
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
