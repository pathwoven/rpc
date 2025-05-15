#ifndef ZK_CLIENT_H
#define ZK_CLIENT_H
#include "RegistryClient.h"
#include "zookeeper/zookeeper.h"
class ZkClient: public RegistryClient{
public:
    ZkClient();
    ~ZkClient();
    void start()override;
    void registerService(std::string service, std::string addr) override;
    void registerMethod(std::string service, std::string method, std::string data="") override;
    // watcher为true表示监听节点变化
    std::string findService(std::string service, bool watcher)override;
private:
    zhandle_t* zh;
    int createNode(const char* path, const char* value, int valueLen, int state);

};
#endif   // ZK_CLIENT_H