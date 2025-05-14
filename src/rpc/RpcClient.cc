#include "RpcClient.h"
#include "MuduoClient.h"

template <typename StubType>
StubType RpcClient::getStub(const std::string& service){
    auto it = channelMap_.find(service);
    std::shared_ptr<RpcChannel> rpcChannel;
    if(it == channelMap_.end()){
        // 建立新的tcpClient todo
        std::string addr = findService(service);
        // 需要确保addr一定是ip:port的形式
        size_t idx = addr.find(':');
        std::string ip = addr.substr(0, idx);
        std::string port = addr.substr(idx+1);
        std::shared_ptr<TCPClient> tcpClient = std::make_shared<TCPClient>(ip, port);
        rpcChannel->setTcp(tcpClient);
        channelMap_.insert({service, rpcChannel});
    }else{
        rpcChannel = it->second;
    }

    return StubType(*rpcChannel);
}

RpcClient::RpcClient(){
    RegistryCliPtr = nullptr;
    MuduoClient::init();
}

std::string RpcClient::findService(const std::string& service){
    // 与注册中心建立连接   并发安全 todo
    if(RegistryCliPtr == nullptr){
        RegistryCliPtr = std::make_unique<ZkClient>();
        RegistryCliPtr->start();
    }
    
    std::string addr = RegistryCliPtr->findService(service);
    if(addr == ""){
        // todo
    }
    return addr;
}