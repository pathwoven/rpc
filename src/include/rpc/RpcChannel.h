#ifndef CHANNEL_H
#define CHANNEL_H
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "ZkClient.h"
#include "TCPClient.h"

class RpcChannel: public google::protobuf::RpcChannel{
public:
    // 调用远程方法
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done) override;
    RpcChannel();
    ~RpcChannel(){}
private:
    std::string serviceName_;
    std::string findService(std::string service);   // 返回服务的地址
    int sk;  // 存放套接字
    void newConnect(std::string addr);
    std::unique_ptr<RegistryCli> RegistryCli;
    // std::unordered_map<std::string, std::unique_ptr<TCPClient>> serviceMap_;  // 服务名与tcp连接的映射
};
#endif CHANNEL_H  // CHANNEL_H