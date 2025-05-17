#include "RpcClient.h"
#include "MuduoClient.h"
#include "Logger.h"

// template <typename StubType>
// std::unique_ptr<StubType> RpcClient::getStub(const std::string& service){
//     auto it = m_channel_map_.find(service);
//     std::shared_ptr<RpcChannel> rpcChannel;
//     if(it == m_channel_map_.end()){
//         // 建立新的tcpClient todo
//         std::string addr = findService(service);
//         // 需要确保addr一定是ip:port的形式
//         size_t idx = addr.find(':');
//         std::string ip = addr.substr(0, idx);
//         std::string port = addr.substr(idx+1);
//         std::shared_ptr<TCPClient> tcpClient = std::make_shared<TCPClient>(ip, port);
//         rpcChannel->setTcp(tcpClient);
//         m_channel_map_.insert({service, rpcChannel});
//     }else{
//         rpcChannel = it->second;
//     }

//     return std::make_unique<StubType>(rpcChannel.get());
// }

RpcClient::RpcClient(){
    RegistryCliPtr = std::make_unique<ZkClient>();
    RegistryCliPtr->start();
    MuduoClient::init();
    Logger::Info("Rpc客户端初始化完毕");
}

std::string RpcClient::findService(const std::string& service){
    // 与注册中心建立连接   并发安全 todo
    
    std::string addr = RegistryCliPtr->findService(service);
    Logger::Debug("RpcClient::findService: "+service+" addr:"+addr);
    if(addr == ""){
        // todo
    }
    return addr;
}