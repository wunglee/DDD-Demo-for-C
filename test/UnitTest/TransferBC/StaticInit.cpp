#include "TransferRepositoryMock.h"
#include "TransferQueryMock.h"
#include "TansferServiceMock.h"
#include "../UserBC/UserServiceMock.h"
#include "TransferDAOMock.h"

TansferServiceMock * TansferServiceMock::转账请求服务_= nullptr;
TransferRepositoryMock* TransferRepositoryMock::转账仓储模拟_=nullptr;
TransferQueryMock* TransferQueryMock::转账查询模拟_=nullptr;
UserServiceMock* UserServiceMock::用户服务模拟_=nullptr;
TransferDAOMock* TransferDAOMock::转账DAO模拟_=nullptr;