#ifndef TRANSFER_RequireInterceptor_H
#define TRANSFER_RequireInterceptor_H
#include "../idempotent/idempotent_manager.h"
#include "../local_transaction/transaction_manager.h"
#include "../naming_service/naming_service_manager.h"
#include "require.h"
#include "require_mappings_manager.h"

class RequireInterceptor {
 private:
  RequireMappingsManager* require_Mappings_Manager = RequireMappingsManager::GetInstance();
  TransactionManager* transactionManager_;
  IdempotentManager* idempotentManager_;
  RequireInterceptor(TransactionManager* transactionManager, IdempotentManager* idempotentManager)
      : transactionManager_(transactionManager), idempotentManager_(idempotentManager) {}
  static RequireInterceptor* requireInterceptor;

 public:
  ~RequireInterceptor() {
    RequireInterceptor::requireInterceptor = nullptr;
    RequireMappingsManager::Destroy_Singleton();
  }
  static RequireInterceptor* BuildInstance(
      TransactionManager* transactionManager = nullptr,
      IdempotentManager* idempotentManager = nullptr) {
    if (RequireInterceptor::requireInterceptor == nullptr) {
      if (transactionManager == nullptr) {
        static TransactionManager _transactionManager;
        transactionManager = &_transactionManager;
      }

      if (idempotentManager == nullptr) {
        static IdempotentManager _idempotentManager;
        idempotentManager = &_idempotentManager;
      }

      RequireInterceptor::requireInterceptor =
          new RequireInterceptor(transactionManager, idempotentManager);
    }
    return RequireInterceptor::requireInterceptor;
  }
  static RequireInterceptor* GetInstance() {
    if (requireInterceptor == nullptr) {
      return BuildInstance();
    }

    return requireInterceptor;
  }
  static void Destroy_Singleton() {
    if (RequireInterceptor::requireInterceptor != nullptr)
      delete RequireInterceptor::requireInterceptor;
  }
  Response Commit(Require& require) {
    Response response;
    try {
      transactionManager_->begin();
      idempotentManager_->check_id(require.Get_Id());
      response = require_Mappings_Manager->Handle(require);
      idempotentManager_->save_id(require.Get_Id());
      transactionManager_->commit();
    } catch (Exception e) {
      transactionManager_->rollback();
      response.exception = std::make_shared<Exception>(e);
    }
    return response;
  }
};

#endif  // TRANSFER_RequireInterceptor_H
