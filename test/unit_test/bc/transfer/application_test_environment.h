#ifndef TRANSFER_ApplicationTestEnvironment_H
#define TRANSFER_ApplicationTestEnvironment_H
#include "../user/user_service_mock.h"
#include "../../../../src/framework_components/naming_service/naming_service_manager.h"
#include "../../../../src/bc/transfer/application/transfer_service.h"
#include "transfer_repository_mock.h"
#include "transfer_query_mock.h"
#include "fund_fervice_remote_mock.h"
class ApplicationTestEnvironment : public ::testing::Test {
public:
    std::vector<Transfer> transfers_;
    TransferRepositoryMock * transferRepositoryMock_= nullptr;
    TransferQueryMock * transferQueryMock_= nullptr;
    UserServiceInterface * userServiceInterface_= nullptr;
    FundServiceRemoteInterface * fund_Service_Remote_Mock = nullptr;
    virtual void SetUp() {
        userServiceInterface_= UserServiceMock::BuildInstance();
        NamingServiceManager::GetInstance()->Add_Service("UserService", (UserServiceInterface *) userServiceInterface_);
        transferRepositoryMock_= TransferRepositoryMock::BuildInstance(transfers_, userServiceInterface_);
        transferQueryMock_=TransferQueryMock::GetInstance(transfers_);
        fund_Service_Remote_Mock=FundServiceRemoteMock::GetInstance();
        NamingServiceManager::GetInstance()->Add_Service("TransferService",
                                                           (TransferServiceInterface *) TransferService::BuildInstance(
                                                                     transferRepositoryMock_, transferQueryMock_, userServiceInterface_,fund_Service_Remote_Mock));
    }
    virtual void TearDown() {
        delete NamingServiceManager::GetInstance()->Remove_Service<UserServiceInterface *>("UserService").value();
        NamingServiceManager::GetInstance()->Remove_Service<TransferServiceInterface *>("TransferService").value();
        TransferService::DestroySingleton();
        delete transferRepositoryMock_;
        delete transferQueryMock_;
        transfers_.clear();
        FundServiceRemoteMock::DestroySingleton();
        NamingServiceManager::Destroy_Singleton();
    }
};


#endif //TRANSFER_ApplicationTestEnvironment_H
