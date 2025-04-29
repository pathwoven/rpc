#ifndef ZK_CLIENT_H
#define ZK_CLIENT_H
#include "RegisterClient.h"
#include "zookeeper/zookeeper.h"
class ZkClient: public RegisterCli{
public:
    ZkClient();
    ~ZkClient();
    void start()override;
    void registerService(std::string service, std::string addr) override;
    void registerMethod(std::string service, std::string method, std::string data="") override;
    std::string findService(std::string service)override;
private:
    zhandle_t* zh;
    void createNode(const char* path, const char* value, int valueLen, int state);

};
#endif ZK_CLIENT_H  // ZK_CLIENT_H