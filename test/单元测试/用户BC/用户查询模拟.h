#ifndef TRANSFER_用户查询模拟_H
#define TRANSFER_用户查询模拟_H
#include "../../../src/用户BC/领域层/用户.h"
#include "../../../src/用户BC/应用层/用户查询接口.h"
class 用户查询模拟: public 用户查询接口{
private:
    std::vector<用户> & 用户集合_;
    用户查询模拟(std::vector<用户> & 用户集合):用户集合_(用户集合){}
    static 用户查询模拟 *用户查询模拟_;
public:
    ~用户查询模拟() {
        用户查询模拟::用户查询模拟_ = nullptr;
    }
    static 用户查询模拟 *构建单例(std::vector<用户> & 用户集合_) {
        if (用户查询模拟_ == nullptr) {
            用户查询模拟_ = new 用户查询模拟(用户集合_);
        }
        return 用户查询模拟_;
    }
    virtual boost::optional<用户> 获取用户(std::string 账号) override{
        for(用户& 用户_:用户集合_){
            if(用户_.获取账号()==账号){
                return 用户(用户_.获取账号(),
                          用户_.是否冻结());
            }
        }
        return boost::none;
    }
};


#endif //TRANSFER_用户查询模拟_H
