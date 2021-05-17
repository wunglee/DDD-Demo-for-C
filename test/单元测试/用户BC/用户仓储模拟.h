#ifndef TRANSFER_用户仓储模拟_H
#define TRANSFER_用户仓储模拟_H
#include "../../../src/用户BC/应用层/用户仓储接口.h"
#include "../../../src/用户BC/应用层/用户仓储接口.h"
#include "../../../src/用户BC/领域层/用户.h"

class 用户仓储模拟: public 用户仓储接口 {
private:
    std::vector<用户> & 用户集合_;
    用户仓储模拟(std::vector<用户> & 用户集合):用户集合_(用户集合){}
    static 用户仓储模拟 *用户仓储模拟_;
public:
    ~用户仓储模拟() {
        用户仓储模拟::用户仓储模拟_ = nullptr;
    }

    static 用户仓储模拟 *构建单例(std::vector<用户> & 用户集合) {
        if (用户仓储模拟_ == nullptr) {
            用户仓储模拟_ = new 用户仓储模拟(用户集合);
        }
        return 用户仓储模拟_;
    }
    static 用户仓储模拟 *获取已存在的单例() {
        return 用户仓储模拟_;
    }
    virtual void 添加用户(std::string 账号) override{
        用户集合_.push_back(用户(账号));
    };
    virtual void 更新用户(用户 &_用户) override{
        for(用户& 用户_:用户集合_){
            if(用户_.获取账号()==_用户.获取账号()){
                _用户.是否冻结()?用户_.冻结():用户_.解冻();
            }
        }
    };
    virtual 用户 获取必须存在的用户(std::string 账号) override{
        for(用户 用户_:用户集合_){
            if(用户_.获取账号()==账号){
                return 用户_;
            }
        }
        throw 异常((boost::format("没有找到用户:%1%")%账号).str());
    }
};

#endif //TRANSFER_用户仓储模拟_H
