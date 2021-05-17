//
// Created by 王立 on 2021/5/15.
//

#ifndef TRANSFER_命令处理器_H
#define TRANSFER_命令处理器_H
#include "处理结果.h"
#include "boost/any.hpp"
class 命令处理器 {
public:
    virtual ~命令处理器(){
    }
    virtual 处理结果 处理(std::string 方法名,const boost::any &方法参数)=0;
};

#endif //TRANSFER_命令处理器_H
