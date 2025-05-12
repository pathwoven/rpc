#include "RpcChannel.h"
#include "Logger.h"

RpcChannel::RpcChannel(){
    reqIdGen_.store(0);
}

// 将rpc请求发送给服务端，同时接受响应
void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response, 
                          google::protobuf::Closure* done)
{
    std::string serviceName = method->service()->name();
    if(serviceName_!=serviceName){   // 需要建立新连接 todo
        // serviceName_ = serviceName;
        // std::string addr = findService(serviceName_);
        // newConnect(addr);
    }
    
    std::string methodName = method->name();
    // 封装头部
    RpcHeader::RequestHeader requestHeader;
    requestHeader.set_service(serviceName);
    requestHeader.set_method(methodName);
    // 设置id获取并加1   todo 32位
    uint32_t reqId = reqIdGen_.fetch_add(1);
    requestHeader.set_id(reqId);
    // 序列化
    std::string header, body;
    if(!requestHeader.SerializeToString(&header)){
        Logger::Error("头部序列化失败");
        controller->SetFailed("头部序列化失败");
        return;
    }
    if(!request->SerializeToString(&body)){
        Logger::Error("请求体序列化失败");
        controller->SetFailed("请求体序列化失败");
        return;
    }

    // 发送请求
    tcpClient_->sendMessage(header, body, reqId, [&done](){
        if(done != nullptr){
            done->Run();   // 运行回调
        }
    });
}

void RpcChannel::setTcp(std::shared_ptr<TCPClient> tcp){
    tcpClient_ = tcp;
}

void RpcChannel::newConnect(std::string addr){
    // 需要确保addr一定是ip:port的形式
    size_t idx = addr.find(':');
    std::string ip = addr.substr(0, idx);
    std::string port = addr.substr(idx+1);
}

