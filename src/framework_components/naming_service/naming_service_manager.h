#ifndef TRANSFER_NamingServiceManager_H
#define TRANSFER_NamingServiceManager_H
#include <map>

#include <boost/any.hpp>

#include "boost/optional.hpp"
/**
 * TODO:这是对服务注册与发现的简单模拟，真实环境会被替换掉
 */
class NamingServiceManager {
 private:
  NamingServiceManager() {}
  std::map<std::string, boost::any> service_map;
  static NamingServiceManager* naming_Service_Manager;

 public:
  ~NamingServiceManager() {
    NamingServiceManager::naming_Service_Manager = nullptr;
    service_map.clear();
  }
  static NamingServiceManager* BuildInstance() {
    if (NamingServiceManager::naming_Service_Manager == nullptr) {
      NamingServiceManager::naming_Service_Manager = new NamingServiceManager();
    }
    return NamingServiceManager::naming_Service_Manager;
  }
  static NamingServiceManager* GetInstance() { return BuildInstance(); }
  static void Destroy_Singleton() {
    if (NamingServiceManager::naming_Service_Manager != nullptr)
      delete NamingServiceManager::naming_Service_Manager;
  }
  template <class T>
  void Add_Service(const std::string name, T Service) {
    service_map[name] = boost::any(Service);
  };
  template <class T>
  boost::optional<T> Remove_Service(const std::string name) {
    boost::optional<T> service_optional = Find_Service<T>(name);
    if (service_optional.has_value()) {
      service_map.erase(name);
    }
    return service_optional;
  };
  template <class T>
  boost::optional<T> Find_Service(const std::string name) {
    boost::any service = service_map[name];
    if (service.empty()) {
      return boost::none;
    }
    return boost::optional<T>(boost::any_cast<T>(service));
  }
};
#endif  // TRANSFER_NamingServiceManager_H
