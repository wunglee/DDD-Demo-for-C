#ifndef DDD_DEMO_FOR_C_TRANSACTION_MANAGER_H
#define DDD_DEMO_FOR_C_TRANSACTION_MANAGER_H

class TransactionManager {
 public:
  virtual ~TransactionManager() {}

 public:
  virtual void begin() {}
  virtual void commit() {}
  virtual void rollback() {}
};

#endif  // DDD_DEMO_FOR_C_TRANSACTION_MANAGER_H
