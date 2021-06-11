#include "transfer_repository_mock.h"
#include "transfer_query_mock.h"
#include "tansfer_service_mock.h"
#include "../user/user_service_mock.h"
#include "transfer_dao_mock.h"
#include "fund_fervice_remote_mock.h"

TansferServiceMock * TansferServiceMock::tansferServiceMock_= nullptr;
TransferRepositoryMock* TransferRepositoryMock::transferRepositoryMock_=nullptr;
TransferQueryMock* TransferQueryMock::transferQueryMock_=nullptr;
UserServiceMock* UserServiceMock::userServiceInterface_=nullptr;
TransferDAOMock* TransferDAOMock::transferDAOMock=nullptr;
FundServiceRemoteMock * FundServiceRemoteMock::fund_Service_Remote_Mock=nullptr;