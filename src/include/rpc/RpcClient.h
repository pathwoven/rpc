#ifndef RPC_CLIENT_H
#define RPC_CLIENT_H
#include <string>
#include "RpcChannel.h"
#include <unordered_map>
class RpcClient {
public: 
    // 从池中获取一个连接，创建stub，并返回给客户
    template <typename StubType>
    std::shared_ptr<StubType> getStub(std::string service);
private:

};
#endif RPC_CLIENT_H  // RPC_CLIENT_H