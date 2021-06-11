#ifndef TRANSFER_RequireMappingMock_H
#define TRANSFER_RequireMappingMock_H
#include "../../../src/framework_components/requestion_filters/require_mapping.h"
#include "../../../src/framework_components/requestion_filters/response.h"
#include <boost/any.hpp>

class RequireMappingMock: public RequireMapping{
public:
    virtual Response handle(std::string function_name, const boost::any &parameters) override {
         Response response;
         response.value=true;
         return response;
    }
};
#endif //TRANSFER_RequireMappingMock_H
