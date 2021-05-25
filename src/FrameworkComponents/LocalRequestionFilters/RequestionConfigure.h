//
// Created by 王立 on 2021/5/24.
//

#ifndef DDD_DEMO_FOR_C_REQUESTIONCONFIGURE_H
#define DDD_DEMO_FOR_C_REQUESTIONCONFIGURE_H
#include "../NamingService/NamingServiceManager.h"
#include "../LocalRequestionFilters/RequestionConfigure.h"
#include "../LocalRequestionFilters/RequiresQueuePoolInterface.h"
#include "../LocalRequestionFilters/RequireMappingsManager.h"
#include "../LocalRequestionFilters/RequireAccepter.h"
#include "RequireMapping.h"
#include "RequiresQueuePool.h"
class RequestionConfigure {
    RequestionConfigure(){
        RequiresQueuePool::构建单例();
        RequireMappingsManager::获取单例();
        RequireAccepter::获取单例();
    }
    static RequestionConfigure* 请求处理配置器_;
public:
    ~RequestionConfigure(){
        RequiresQueuePool::销毁单例();
        RequireMappingsManager::销毁单例();
        RequireAccepter::销毁单例();
        RequestionConfigure::请求处理配置器_= nullptr;
    }
    static RequestionConfigure* 构建单例(){
        if(请求处理配置器_== nullptr){
            请求处理配置器_=new RequestionConfigure();
        }
        return 请求处理配置器_;
    }
    static RequestionConfigure* 获取单例(){
        return 构建单例();
    }
    static void 销毁单例(){
        delete RequestionConfigure::请求处理配置器_;
    }
    void 注册请求处理器(std::string 名称, RequireMapping *请求处理器){
        RequireMappingsManager::获取单例()->注册请求处理器(名称, 请求处理器);
    }
    void 注销请求处理器(std::string 名称){
        RequireMappingsManager::获取单例()->注销请求处理器(名称);
    }
};


#endif //DDD_DEMO_FOR_C_REQUESTIONCONFIGURE_H
