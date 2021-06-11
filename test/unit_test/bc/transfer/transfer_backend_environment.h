#ifndef TRANSFER_TransferBackendEnvironment_H
#define TRANSFER_TransferBackendEnvironment_H
#include "gtest/gtest.h"
#include "transfer_dao_mock.h"
#include "../../../../src/bc/transfer/backend_adapters/transfer_repository.h"

class TransferBackendEnvironment : public ::testing::Test {
public:
    TransferDAOMock * transferDAOMock= nullptr;
    UserServiceInterface * userServiceInterface_= nullptr;
    virtual void SetUp() {
        userServiceInterface_= UserServiceMock::BuildInstance();
        transferDAOMock=TransferDAOMock::GetInstance();
        TransferRepository::BuildInstance(transferDAOMock, userServiceInterface_);
    }
    virtual void TearDown() {
        delete userServiceInterface_;
        delete transferDAOMock;
        TransferRepository::DestroyInstance();
    }
};


#endif //TRANSFER_TransferBackendEnvironment_H
