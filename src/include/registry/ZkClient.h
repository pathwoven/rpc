#ifndef ZK_CLIENT_H
#define ZK_CLIENT_H
#include "RegistryClient.h"
#include <unordered_map>
#include <vector>
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
    zhandle_t* zh;     // 线程安全（但是初始化和销毁需要在单线程下）
    int createNode(const char* path, const char* value, int valueLen, int state);

    std::mutex servicesMutex_;
    struct ServiceInfo{
        std::string addr;
        int weight;
    };
    // 存储服务实例地址
    std::unordered_map<std::string, std::vector<ServiceInfo>> m_services_addr_;

};
#endif   // ZK_CLIENT_H