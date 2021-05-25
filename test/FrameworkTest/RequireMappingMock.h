#ifndef TRANSFER_模拟处理器_H
#define TRANSFER_模拟处理器_H
#include "../../src/FrameworkComponents/LocalRequestionFilters/RequireMapping.h"
#include "../../src/FrameworkComponents/LocalRequestionFilters/Response.h"
#include <boost/any.hpp>

class RequireMappingMock: public RequireMapping{
public:
    virtual Response 处理(std::string 方法名, const boost::any &方法参数) override {
         Response 处理结果_;
         处理结果_.返回值=true;
         return 处理结果_;
    }
};
#endif //TRANSFER_模拟处理器_H
