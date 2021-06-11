#ifndef TRANSFER_RequireMapping_H
#define TRANSFER_RequireMapping_H
#include "response.h"
#include "boost/any.hpp"
class RequireMapping {
public:
    virtual ~RequireMapping(){
    }

    virtual Response handle(std::string function_name, const boost::any &parameters)=0;
};

#endif //TRANSFER_RequireMapping_H
