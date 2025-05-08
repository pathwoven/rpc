#include "RpcClient.h"

template <typename StubType>
StubType RpcClient::getStub(const std::string& service){
    auto it = tcpMap_.find(service);
    TCPClient* tcpClient;
    if(it == tcpMap_.end()){
        // 建立新的tcpClient todo
        std::string addr = findService(service);
        // 需要确保addr一定是ip:port的形式
        size_t idx = addr.find(':');
        std::string ip = addr.substr(0, idx);
        std::string port = addr.substr(idx+1);
        tcpClient = TCPClient(ip, port);
        tcpMap_.insert({service, tcpClient});
    }else{
        tcpClient = it->second;
    }
    RpcChannel rpcChannel{};
    rpcChannel.setTcp(tcpClient);

    return StubType(rpcChannel);
}

RpcClient::RpcClient(){
    RegistryCli = nullptr;
}

std::string RpcClient::findService(const std::string& service){
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