#ifndef DDD_DEMO_FOR_C_DALSET_TRANSACTION_MANAGER_H
#define DDD_DEMO_FOR_C_DALSET_TRANSACTION_MANAGER_H

#include <memory>

#include "mm3rd/fmt/include/fmt/chrono.h"

#include "../exception.h"
#include "comm/dal_set/src/mysqlstorage.h"
#include "transaction_manager.h"

class MysqlTransactionManager : public TransactionManager {
 public:
  static MysqlTransactionManager* BuildInstance(std::shared_ptr<dalset::CMySqlStorage> connection) {
    if (mysql_transaction_manager_ == nullptr) {
      static MysqlTransactionManager dalset_transaction_manager(connection);
      mysql_transaction_manager_ = &dalset_transaction_manager;
    }
    return mysql_transaction_manager_;
  }

  static MysqlTransactionManager* GetInstance() {
    if (mysql_transaction_manager_ == nullptr) {
      throw Exception("MysqlTransactionManager实例未初始化");
    }
    return mysql_transaction_manager_;
  }

 public:
  void begin() {
    int retcode = connection_->BeginTransaction();
    if (retcode != 0) {
      throw Exception(fmt::format("Begin错误|retcode={retcode}", fmt::arg("retcode", retcode)));
    }
  }
  void commit() {
    int retcode = connection_->CommitTransaction();
    if (retcode != 0) {
      throw Exception(fmt::format("Commit错误|retcode={retcode}", fmt::arg("retcode", retcode)));
    }
  }
  void rollback() {
    int retcode = connection_->RollBackTransaction();
    if (retcode != 0) {
      throw Exception(fmt::format("RollBack错误|retcode={retcode}", fmt::arg("retcode", retcode)));
    }
  }

  void SetConnection(std::shared_ptr<dalset::CMySqlStorage> connection) {
    connection_ = connection;
  }

 private:
  MysqlTransactionManager(std::shared_ptr<dalset::CMySqlStorage> connection)
      : connection_(connection) {}

 private:
  std::shared_ptr<dalset::CMySqlStorage> connection_;
  static MysqlTransactionManager* mysql_transaction_manager_;
};

#endif  // DDD_DEMO_FOR_C_TRANSACTION_MANAGER_H
