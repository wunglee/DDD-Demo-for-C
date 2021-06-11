#ifndef TRANSFER_TransferUser_H
#define TRANSFER_TransferUser_H
#include <string>

class TransferUser {
public:
    const std::string acount_id_;
    const bool frozen_;
    TransferUser(const std::string acount_id, bool frozen=false) :
            acount_id_(acount_id), frozen_(frozen) {}
};
#endif //TRANSFER_TransferUser_H
