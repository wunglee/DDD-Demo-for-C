#ifndef TRANSFER_FundRepositoryInterface_H
#define TRANSFER_FundRepositoryInterface_H
#include "../domain/fund.h"
#include "boost/optional.hpp"
class FundRepositoryInterface {
public:
    virtual ~FundRepositoryInterface(){}
    virtual Fund GetExisted(std::string name)=0;
    virtual void Create(Fund& fund)=0;
    virtual void Update(Fund& fund)=0;
};
#endif //TRANSFER_FundRepositoryInterface_H
