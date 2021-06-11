#ifndef TRANSFER_RequireMappingsManager_H
#define TRANSFER_RequireMappingsManager_H

#include <map>
#include "require_mapping.h"
#include "../naming_service/naming_service_manager.h"
#include "filter.h"
#include "filters_manager.h"
#include "require.h"
#include "response.h"
#include "../exception.h"

/**
 * TODO:请求处理器线程和请求发送方线程处于同一微服务，它完成微服务自身的横切业务的拦截处理，
 * 拦截后有可能需要转发到其它微服务进一步处理。
 */
class RequireMappingsManager {
private:
    std::map<std::string, RequireMapping *> require_Mapping_Map;

    RequireMappingsManager(const std::list<Filter *> filters = std::list<Filter *>()) {
        filters_Manager = new FiltersManager(filters);
    }

    static RequireMappingsManager *require_Mappings_Manager;
    FiltersManager *filters_Manager;
public:
    ~RequireMappingsManager() {
        require_Mapping_Map.clear();
        delete filters_Manager;
        RequireMappingsManager::require_Mappings_Manager = nullptr;
    }

    static RequireMappingsManager *BuildInstance(const std::list<Filter *> filters = std::list<Filter *>()) {
        if (RequireMappingsManager::require_Mappings_Manager == nullptr) {
            RequireMappingsManager::require_Mappings_Manager = new RequireMappingsManager(filters);
        }
        return RequireMappingsManager::require_Mappings_Manager;
    }

    static RequireMappingsManager *GetInstance() {
        return BuildInstance();
    }

    static void Destroy_Singleton() {
        if (RequireMappingsManager::require_Mappings_Manager != nullptr)
            delete RequireMappingsManager::require_Mappings_Manager;
    }

    Response Handle(Require &require) {
        RequireMapping *require_Mapping = require_Mapping_Map[require.Get_Mapping_Name()];
        return filters_Manager->Handle(*require_Mapping,
                                                    require.Get_Function_Name(),
                                                    require.Get_Parameters(),
                                                    require.Get_Filter_Config());
    }

    void Add_Require_Mapping(std::string name, RequireMapping *require_Mapping) {
        require_Mapping_Map[name] = require_Mapping;
    }

    void Remove_Require_Mapping(std::string name) {
        require_Mapping_Map.erase(name);
    }
};


#endif //TRANSFER_RequireMappingsManager_H
