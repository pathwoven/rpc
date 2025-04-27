#ifndef CHANNEL_H
#define CHANNEL_H
#include "google/protobuf/service.h"

class Channel: public google::protobuf::RpcChannel{
public:
    // 调用远程方法
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done) override;
    Channel(){}
    ~Channel(){}
private:
    void findService();
};
#endif CHANNEL_H  // CHANNEL_H