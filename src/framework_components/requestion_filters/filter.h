#ifndef TRANSFER_Filter_H
#define TRANSFER_Filter_H

class Filter{
public:
    const std::string name_;
    Filter(const std::string name) : name_(name) {}
    //TODO:boost::any如何被处理？需要可以反射来获取内部数据的能力
    virtual void Before_Executing(std::string name, const boost::any parameters)=0;
    virtual void After_Executing(std::string name, const boost::any parameters, Response &response)=0;
};
#endif //TRANSFER_Filter_H
