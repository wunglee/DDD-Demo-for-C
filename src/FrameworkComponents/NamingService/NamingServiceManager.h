#ifndef TRANSFER_命名服务管理器_H
#define TRANSFER_命名服务管理器_H

#include <boost/any.hpp>
#include <boost/optional.hpp>
/**
 * TODO:这是对服务注册与发现的简单模拟，真实环境会被替换掉
 */
class NamingServiceManager{
private:
    NamingServiceManager(){}
    std::map<std::string,boost::any> 命名服务注册表;
    static NamingServiceManager* 命名服务管理器_;
public:
    ~NamingServiceManager() {
        NamingServiceManager::命名服务管理器_= nullptr;
        命名服务注册表.clear();
    }
    static NamingServiceManager* 构建单例(){
        if (NamingServiceManager::命名服务管理器_ == nullptr) {
            NamingServiceManager::命名服务管理器_ = new NamingServiceManager();
        }
        return NamingServiceManager::命名服务管理器_;
    }
    static NamingServiceManager* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        if(NamingServiceManager::命名服务管理器_ != nullptr)
          delete NamingServiceManager::命名服务管理器_;
    }
    template<class T>
    void 注册服务(const std::string 对象名, T 对象) {
        命名服务注册表[对象名]=boost::any(对象);
    };
    template<class T>
    boost::optional<T> 注销服务(const std::string 服务名) {
        boost::optional<T> 对象_= 查找服务<T>(服务名);
        if(对象_.has_value()){
            命名服务注册表.erase(服务名);
        }
        return 对象_;
    };
    template<class T>
    boost::optional<T> 查找服务(const std::string 对象名){
        boost::any 对象 = 命名服务注册表[对象名];
        if(对象.empty()) {
            return boost::none;
        }
        return boost::optional<T>(boost::any_cast<T>(对象));
    }
};
#endif //TRANSFER_命名服务管理器_H