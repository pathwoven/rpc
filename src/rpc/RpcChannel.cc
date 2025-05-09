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
        // serviceName_ = serviceName;
        // std::string addr = findService(serviceName_);
        // newConnect(addr);
    }
    
    std::string methodName = method->name();
    // 封装头部
    RpcHeader::RequestHeader requestHeader;
    requestHeader.set_service(serviceName);
    requestHeader.set_method(methodName);
    // 序列化
    std::string header, body;
    if(!requestHeader.SerializeToString(&header)){
        // todo error
    }
    if(!request->SerializeToString(&body)){
        // todo error
    }

}

void RpcChannel::setTcp(const TCPClient& tcp){
    tcpClient_ = tcp;
}

void RpcChannel::newConnect(std::string addr){
    // 需要确保addr一定是ip:port的形式
    size_t idx = addr.find(':');
    std::string ip = addr.substr(0, idx);
    std::string port = addr.substr(idx+1);
}

