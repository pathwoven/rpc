#include "RpcChannel.h"

// 将rpc请求发送给服务端，同时接受响应
void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done)
{
    std::string serviceName = method->service()->name();
    if(serviceName_!=serviceName){   // 需要建立新连接
        serviceName_ = serviceName;
        std::string addr = findService(serviceName_);
        newConnect(addr);
    }
    
    // 封装数据
    std::string methodName = method->name();
    // 封装头部
    
}

RpcChannel::RpcChannel(){
    RegistryCli = nullptr;
    serviceName_ = "";
}

void RpcChannel::newConnect(std::string addr){
    
}

std::string RpcChannel::findService(std::string service){
    // 与注册中心建立连接   并发安全 todo
    if(RegistryCli == nullptr){
        RegistryCli = std::make_unique<ZkClient>();
        RegistryCli->start();
    }
    
    std::string addr = RegistryCli->findService(service);
    if(addr == ""){
        // todo
    }
    return addr;
}