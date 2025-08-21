#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H
#include <string>
#include <unordered_map>
#include <MuduoClient.h>
#include "RpcChannel.h"
#include "Logger.h"
#include "ZkClient.h"
class RpcClient {
public: 
    RpcClient();
    // 从池中获取一个连接，创建stub，并返回给客户  todo
    template <typename StubType>
    std::unique_ptr<StubType> getStub(const std::string& service){
        std::shared_ptr<RpcChannel> rpcChannel;
        {
            std::lock_guard<std::mutex> lock(channelMutex_);
            auto it = m_channel_map_.find(service);
            if(it == m_channel_map_.end()){
                // 建立新的tcpClient todo
                std::string addr = findService(service);
                // 需要确保addr一定是ip:port的形式
                size_t idx = addr.find(':');
                std::string ip = addr.substr(0, idx);
                std::string port = addr.substr(idx+1);
                std::shared_ptr<TCPClient> tcpClient = std::make_shared<MuduoClient>(ip, port);
                rpcChannel = std::make_shared<RpcChannel>();
                rpcChannel->setTcp(tcpClient);
                m_channel_map_.insert({service, rpcChannel});
                Logger::Info("RpcClient::getStub() 创建新的rpcChannel，连接至 "+ip+":"+port);
            }else{
                rpcChannel = it->second;
            }
        }
        

        return std::make_unique<StubType>(rpcChannel.get());
    }
private:
    // std::unordered_map<std::string, std::string> addrMap_;    // 服务名与地址的映射   
    std::mutex channelMutex_;
    std::unordered_map<std::string, std::shared_ptr<RpcChannel>> m_channel_map_;  // 服务名与channel的map
    // 连接池的最大连接数
    int maxConn = 3;

    std::unique_ptr<RegistryClient> RegistryCliPtr;
    std::string findService(const std::string& service);    // 返回服务的地址
};
#endif   // RPC_CLIENT_H