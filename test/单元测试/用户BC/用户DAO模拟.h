#ifndef TRANSFER_用户DAO模拟_H
#define TRANSFER_用户DAO模拟_H
#include "../../../src/用户BC/从适配器/用户DAO接口.h"
#include "../../../src/用户BC/从适配器/用户PO.h"
class 用户DAO模拟: public 用户DAO接口 {
private:
    std::vector<用户PO> 用户PO集合_;
    static 用户DAO模拟 * 用户DAO模拟_;
public:
    ~用户DAO模拟() {
        用户DAO模拟::用户DAO模拟_ = nullptr;
        用户PO集合_.clear();
    }
    static 用户DAO模拟 *构建单例() {
        if (用户DAO模拟_ == nullptr) {
            用户DAO模拟_ = new 用户DAO模拟();
        }
        return 用户DAO模拟_;
    }

    virtual boost::optional<用户PO> 获取用户PO(std::string 账号) override{
        for (用户PO &用户PO_:用户PO集合_) {
            if (用户PO_.账号_ == 账号) {
                return 用户PO_;
            }
        }
        return boost::none;
    }
    virtual void 添加用户PO(const 用户PO 用户PO_) override{
        用户PO集合_.push_back(用户PO_);
    };
    virtual void 更新用户PO(const 用户PO _用户PO) override{
        for (用户PO &用户PO_:用户PO集合_) {
            if (用户PO_.账号_ == _用户PO.账号_) {
                用户PO_.是否冻结_=_用户PO.是否冻结_;
            }
        }
    };
};


#endif //TRANSFER_用户DAO模拟_H
