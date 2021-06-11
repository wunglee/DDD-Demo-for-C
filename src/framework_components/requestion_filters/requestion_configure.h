#ifndef DDD_DEMO_FOR_C_REQUESTION_CONFIGURE_H
#define DDD_DEMO_FOR_C_REQUESTION_CONFIGURE_H
#include "../naming_service/naming_service_manager.h"
#include "../requestion_filters/requestion_configure.h"
#include "../requestion_filters/require_mappings_manager.h"
#include "../requestion_filters/require_interceptor.h"
#include "require_mapping.h"
class RequestionConfigure {
    RequestionConfigure(){
        RequireMappingsManager::GetInstance();
        RequireInterceptor::GetInstance();
    }
    static RequestionConfigure* requestion_Configure;
public:
    ~RequestionConfigure(){
        RequireMappingsManager::Destroy_Singleton();
        RequireInterceptor::Destroy_Singleton();
        RequestionConfigure::requestion_Configure= nullptr;
    }
    static RequestionConfigure* BuildInstance(){
        if(requestion_Configure == nullptr){
            requestion_Configure=new RequestionConfigure();
        }
        return requestion_Configure;
    }
    static RequestionConfigure* GetInstance(){
        return BuildInstance();
    }
    static void DestroyInstance(){
        delete RequestionConfigure::requestion_Configure;
    }
    void Add_Require_Mapping(std::string name, RequireMapping *require_Mapping){
        RequireMappingsManager::GetInstance()->Add_Require_Mapping(name, require_Mapping);
    }
    void Remove_Require_Mapping(std::string name){
        RequireMappingsManager::GetInstance()->Remove_Require_Mapping(name);
    }
};


#endif //DDD_DEMO_FOR_C_REQUESTION_CONFIGURE_H
