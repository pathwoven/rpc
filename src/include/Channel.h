#ifndef CHANNEL_H
#define CHANNEL_H
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "ZkClient.h"

class Channel: public google::protobuf::RpcChannel{
public:
    // 调用远程方法
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done) override;
    Channel();
    ~Channel(){}
private:
    std::string findService(std::string service);   // 返回服务的地址

    std::unique_ptr<RegisterCli> registerCli;
    std::unordered_map<std::string, std::string> serviceMap;  // 服务名与服务地址的映射
};
#endif CHANNEL_H  // CHANNEL_H