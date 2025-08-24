#ifndef RPC_CONFIG_H
#define RPC_CONFIG_H

#include <string>
#include <vector>

class RpcConfig{
public:
    static void loadFromFile(std::string file);
    static std::string zookeeperAddr;
};

#endif  // RPC_CONFIG_H