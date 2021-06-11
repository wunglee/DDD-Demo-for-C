#ifndef TRANSFER_UserQueryService_H
#define TRANSFER_UserQueryService_H
#include "boost/optional.hpp"
#include <string>
class UserQueryService {
public:
    virtual ~UserQueryService(){}
    virtual boost::optional<User> GetUser(std::string account_id) =0;
};


#endif //TRANSFER_UserQueryService_H
