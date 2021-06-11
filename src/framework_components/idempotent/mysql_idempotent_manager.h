#ifndef DDD_DEMO_FOR_C_MYSQL_IDEMPOTENT_MANAGER_H
#define DDD_DEMO_FOR_C_MYSQL_IDEMPOTENT_MANAGER_H

#include <memory>

#include "mm3rd/fmt/include/fmt/chrono.h"

#include "appplatform/export_include/comm/dal_set/src/resultset.h"

#include "../exception.h"
#include "comm/dal_set/src/mysqlstorage.h"
#include "idempotent_manager.h"

class MysqlIdempotentManager : public IdempotentManager {
 public:
  static MysqlIdempotentManager* BuildInstance(std::shared_ptr<dalset::CMySqlStorage> connection) {
    if (mysql_idempotent_manager_ == nullptr) {
      static MysqlIdempotentManager mysql_idempotent_manager(connection);
      mysql_idempotent_manager_ = &mysql_idempotent_manager;
    }
    return mysql_idempotent_manager_;
  }

  static MysqlIdempotentManager* GetInstance() {
    if (mysql_idempotent_manager_ == nullptr) {
      throw Exception("MysqlIdempotentManager实例未初始化");
    }
    return mysql_idempotent_manager_;
  }

 public:
  void check_id(std::string id) override {
    std::stringstream sql_stream;
    sql_stream << "select FId from T_Idempotent where FId="
               << "'" << connection_->EscapeString(id) << "';";

    std::string sql = sql_stream.str();

    dalset::IResultSet& mysql_result = connection_->QueryForResultSet(sql.c_str(), true);
    if (!mysql_result.IsReady()) {
      //查询执行失败
      throw Exception(fmt::format("sql执行失败:sql={sql}", fmt::arg("sql", sql)));
    }

    // 4.后置校验
    if (mysql_result.First()) {
      // Get实体数据为空
      throw Exception(fmt::format("重入请求:id={id}", fmt::arg("id", id)));
    }
  }
  void save_id(std::string id) override {
    std::stringstream sql_stream;
    sql_stream << "insert T_Idempotent set FId="
               << "'" << connection_->EscapeString(id) << "'";

    std::string sql = sql_stream.str();
    int retcode = connection_->Update(sql.c_str());
    if (retcode != 0) {
      throw Exception(fmt::format("插入幂等ID失败|sql={sql}", fmt::arg("sql", sql)));
    }
  }

  void SetConnection(std::shared_ptr<dalset::CMySqlStorage> connection) {
    connection_ = connection;
  }

  virtual ~MysqlIdempotentManager() {}

 private:
  explicit MysqlIdempotentManager(std::shared_ptr<dalset::CMySqlStorage> connection)
      : connection_(connection) {}

 private:
  std::shared_ptr<dalset::CMySqlStorage> connection_;
  static MysqlIdempotentManager* mysql_idempotent_manager_;
};

#endif  // DDD_DEMO_FOR_C_IDEMPOTENT_MANAGER_H
