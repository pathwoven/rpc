#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H
#include <string>
#include <unordered_map>
#include "RpcChannel.h"
#include "ZkClient.h"
class RpcClient {
public: 
    // 从池中获取一个连接，创建stub，并返回给客户
    template <typename StubType>
    StubType getStub(const std::string& service);
private:
    RpcClient();
    // std::unordered_map<std::string, std::string> addrMap_;    // 服务名与地址的映射   
    std::unordered_map<std::string, TCPClient> tcpMap_;  // 服务名与tcp连接的map

    std::unique_ptr<RegistryCli> RegistryCli;
    std::string RpcClient::findService(const std::string& service);    // 返回服务的地址
};
#endif RPC_CLIENT_H  // RPC_CLIENT_H