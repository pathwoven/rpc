#include "Channel.h"

// 将rpc请求发送给服务端，同时接受响应
void Channel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done)
{
    std::string serviceName = method->service()->name();
}

Channel::Channel(){
    registerCli = nullptr;
}

std::string Channel::findService(std::string service){
    // 与注册中心建立连接   并发安全 todo
    if(registerCli == nullptr){
        registerCli = std::make_unique<ZkClient>();
        registerCli->start();
    }
    
    std::string addr = registerCli->findService(service);
    if(addr == ""){
        // todo
    }
    return addr;
}