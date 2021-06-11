#ifndef ProtobufRequireAdaptor_H
#define ProtobufRequireAdaptor_H
#include "../../../framework_components/requestion_filters/response.h"
#include "../../../framework_components/requestion_filters/require.h"
#include "../../../framework_components/requestion_filters/require_interceptor.h"
#include "../../../framework_components/naming_service/naming_service_manager.h"
#include "../../../global_business_dependency/service_interfaces/transfer/transfer_dto.h"
class ProtobufRequireAdaptor {
private:
    RequireInterceptor * require_interceptor_= nullptr;
    static ProtobufRequireAdaptor * protobufRequireAdaptor_;
    ProtobufRequireAdaptor(RequireInterceptor *require_interceptor_) : require_interceptor_(require_interceptor_) {}
public:
    ~ProtobufRequireAdaptor() {
        ProtobufRequireAdaptor::protobufRequireAdaptor_= nullptr;
    }
    static ProtobufRequireAdaptor* BuildInstance(RequireInterceptor * require_interceptor_){
        if (protobufRequireAdaptor_ == nullptr) {
            protobufRequireAdaptor_ = new ProtobufRequireAdaptor(require_interceptor_);
        }
        return protobufRequireAdaptor_;
    }
    static ProtobufRequireAdaptor* GetInstance(){
        if(ProtobufRequireAdaptor::protobufRequireAdaptor_ == nullptr){
            throw "单例未创建";
        }
        return protobufRequireAdaptor_;
    }
    static void DestroyInstance(){
        if(ProtobufRequireAdaptor::protobufRequireAdaptor_ != nullptr){
            delete protobufRequireAdaptor_;
        }
    }
    int ApplyTransfer(std::string require_id,ApplyTransferDTO & applyTransferDTO){
        Require require(require_id,"TransferRequireMapping","ApplyTransfer",applyTransferDTO);;
        Response response=require_interceptor_->Commit(require);
        return boost::any_cast<int>(response.value);
    }
};


#endif //ProtobufRequireAdaptor_H
