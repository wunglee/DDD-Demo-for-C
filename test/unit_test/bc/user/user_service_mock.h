#ifndef TRANSFER_UserServiceMock_H
#define TRANSFER_UserServiceMock_H
#include "../../../../src/global_business_dependency/service_interfaces/user/user_service_interface.h"

class UserServiceMock: public UserServiceInterface{
private:
    std::map<std::string,bool> lockedStatus;
    static UserServiceMock* userServiceInterface_;
public:
    ~UserServiceMock() {
        UserServiceMock::userServiceInterface_= nullptr;
        lockedStatus.clear();
    }
    static UserServiceMock* BuildInstance(){
        if (userServiceInterface_ == nullptr) {
            userServiceInterface_ = new UserServiceMock();
        }
        return userServiceInterface_;
    }
    static void DestroyInstance(){
        if (userServiceInterface_ != nullptr) {
            delete userServiceInterface_;
        }
    }
    static UserServiceMock* GetInstance(){
        return BuildInstance();
    }
    virtual void AddUser(std::string account_id) override {
        if(lockedStatus.find(account_id) == lockedStatus.end())
            lockedStatus[account_id]=false;
    };
    virtual void FreezeUser(std::string account_id) override{
        if(lockedStatus.find(account_id) != lockedStatus.end())
            lockedStatus[account_id]=true;
    };
    virtual void UnfreezeUser(std::string account_id) override{
        if(lockedStatus.find(account_id) != lockedStatus.end())
            lockedStatus[account_id]=false;
    };
    virtual bool IsFrozen(std::string account_id) override{
        return lockedStatus[account_id];
    };
    virtual boost::optional<UserDTO> GetUser(std::string account_id) override{
        return UserDTO(account_id, lockedStatus[account_id]);
    };
};


#endif //TRANSFER_UserServiceMock_H
