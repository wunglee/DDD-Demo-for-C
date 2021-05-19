#ifndef TRANSFER_命令队列池_H
#define TRANSFER_命令队列池_H
#include "vector"
#include "命令队列.h"
#include "命令队列池接口.h"
class 命令队列池 : public 命令队列池接口 {
private:
    std::list<命令队列> 队列池_;
    static 命令队列池 * 命令队列池_;
    命令队列池(int 大小=10){
        for(int i=0;i<大小;i++){
            队列池_.push_back(命令队列());
        }
    }
public:
    virtual ~命令队列池(){
        队列池_.clear();
        命令队列池::命令队列池_= nullptr;
    }
    static 命令队列池* 构建单例(int 大小=10){
        if(命令队列池::命令队列池_ == nullptr){
            命令队列池::命令队列池_=new 命令队列池(大小);
        }
        return 命令队列池::命令队列池_;
    }
    static 命令队列池* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(命令队列池::命令队列池_!= nullptr)
            delete 命令队列池::命令队列池_;
    }
    void 加入命令(命令& 命令) {
        boost::optional<命令队列&> 命令队列_= 选择最小队列();
        if(命令队列_.has_value()){
            命令队列_.value().加入命令(命令);
        }
    }
    boost::optional<命令>  取出命令() {
        boost::optional<命令队列&> 命令队列_= 选择最大队列();
        if(命令队列_.has_value()){
            return 命令队列_.value().取出命令();
        }
        return boost::none;
    }
    boost::optional<命令队列&> 选择最小队列(){
        long 最小值=std::numeric_limits<long>::max();
        命令队列* 选择的命令队列= nullptr;
        for(命令队列& 命令队列_:队列池_){
            int 当前大小=命令队列_.队列大小();
            if(当前大小<最小值){
                最小值=当前大小;
                选择的命令队列=&命令队列_;
                if(最小值==0) break;
            }
        }
        return *选择的命令队列;
    }
    boost::optional<命令队列&> 选择最大队列(){
        long 最大值=0;
        命令队列* 选择的命令队列= nullptr;
        for(命令队列& 命令队列_:队列池_){
            int 当前大小=命令队列_.队列大小();
            if(当前大小>最大值){
                最大值=当前大小;
                选择的命令队列=&命令队列_;
            }
        }
        return *选择的命令队列;
    }
};


#endif //TRANSFER_命令队列池_H
