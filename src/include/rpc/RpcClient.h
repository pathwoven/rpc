#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H
#include <string>
#include "RpcChannel.h"
#include <unordered_map>
class RpcClient {
public: 
    // 从池中获取一个某服务对应的RpcChannel，并返回一个stub给客户
    RpcChannel* getStub(std::string service);
private:

};
#endif RPC_CLIENT_H  // RPC_CLIENT_H