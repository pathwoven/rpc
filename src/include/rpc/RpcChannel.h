#ifndef CHANNEL_H
#define CHANNEL_H
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "RpcHeader.pb.h"
#include "TCPClient.h"

class RpcChannel: public google::protobuf::RpcChannel{
public:   
    // 调用远程方法
    void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done) override;
    void setTcp(const TCPClient& tcp);
private:
    std::string serviceName_;
    TCPClient tcpClient_;
    void newConnect(std::string addr);
    // std::unordered_map<std::string, std::unique_ptr<TCPClient>> serviceMap_;  // 服务名与tcp连接的映射
};
#endif CHANNEL_H  // CHANNEL_H