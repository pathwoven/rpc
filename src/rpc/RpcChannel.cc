#include "RpcChannel.h"

// 将rpc请求发送给服务端，同时接受响应
void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done)
{
    std::string serviceName = method->service()->name();

    auto sm = serviceMap.find(serviceName);
    // 假如此前没有建立连接
    if( sm == serviceMap.end()){
        // 建立连接 todo
        // 查询服务
        std::string addr = findService(serviceName);
    }else{

    }

}

RpcChannel::RpcChannel(){
    RegistryCli = nullptr;
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