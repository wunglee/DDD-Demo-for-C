#ifndef TRANSFER_MYSQL_PublishSubscribeService_H
#define TRANSFER_MYSQL_PublishSubscribeService_H

#include <memory>
#include <string>

#include "boost/optional.hpp"
#include "mm3rd/fmt/include/fmt/chrono.h"

#include "../exception.h"
#include "comm/dal_set/src/mysqlstorage.h"
#include "domain_event.h"
#include "event_monitor.h"
#include "publish_subscribe_service_handler.h"

class MysqlPublishSubscribeService : public PublishSubscribeServiceHandler {
 private:
  MysqlPublishSubscribeService(std::shared_ptr<dalset::CMySqlStorage> connection)
      : connection_(connection) {}
  static MysqlPublishSubscribeService* publish_Subscribe_Service;

 public:
  virtual ~MysqlPublishSubscribeService() {
    MysqlPublishSubscribeService::publish_Subscribe_Service = nullptr;
  }
  static MysqlPublishSubscribeService* BuildInstance(
      std::shared_ptr<dalset::CMySqlStorage> connection) {
    if (publish_Subscribe_Service == nullptr) {
      publish_Subscribe_Service = new MysqlPublishSubscribeService(connection);
    }
    return publish_Subscribe_Service;
  }
  static MysqlPublishSubscribeService* GetInstance() {
    if (publish_Subscribe_Service == nullptr) {
      throw Exception("MysqlPublishSubscribeService实例未设置");
    }
    return publish_Subscribe_Service;
  }
  static void DestoryInstance() { delete MysqlPublishSubscribeService::publish_Subscribe_Service; }
  void Subscribe(std::string event_name, std::string monitor_name) override {}
  void Publish(DomainEvent domain_Event) override {
    std::stringstream sql_stream;
    sql_stream << "insert T_DomainEvent set FName="
               << "'" << connection_->EscapeString(domain_Event.Get_Name()) << "'"
               << " ,FTransactionId="
               << "'"
               << connection_->EscapeString(std::to_string(domain_Event.Get_Transaction_Id()))
               << "'"
               << " ,FContent="
               << "'" << connection_->EscapeString(domain_Event.Get_Content()) << "'";

    std::string sql = sql_stream.str();
    int retcode = connection_->Update(sql.c_str());
    if (retcode != 0) {
      throw Exception(fmt::format("插入领域事件失败|sql={sql}", fmt::arg("sql", sql)));
    }
  }
  void ClearMonitors() override {}
  void SetConnection(std::shared_ptr<dalset::CMySqlStorage> connection) {
    connection_ = connection;
  }

 private:
  std::shared_ptr<dalset::CMySqlStorage> connection_;
};

#endif  // TRANSFER_MYSQL_PublishSubscribeService_H
