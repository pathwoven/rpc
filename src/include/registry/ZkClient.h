#ifndef ZK_CLIENT_H
#define ZK_CLIENT_H
#include "RegistryClient.h"
#include "RoundRobin.h"
#include "ServiceInfo.h"

#include <unordered_map>
#include <vector>
#include <mutex>
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
    void setLoadBalancer(LoadBalancer* lb);
    
   
private:
    zhandle_t* zh;     // 线程安全（但是初始化和销毁需要在单线程下）
    int createNode(const char* path, const char* value, int valueLen, int state);

    static void globalWatcher(zhandle_t *zh, int type, int state, const char *path,void *watcherCtx);

    std::mutex servicesMutex_;
    
    // 存储服务实例信息
    std::unordered_map<std::string, std::vector<ServiceInfo>> m_services_info_;

    // 负载均衡
    std::mutex balancerMutex_;
    std::unique_ptr<LoadBalancer> m_lb_;

};
#endif   // ZK_CLIENT_H