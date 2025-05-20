#include "ZkClient.h"
#include "Logger.h"
#include <vector>

// 全局观察器，用于接收ZooKeeper服务器的通知
void ZkClient::globalWatcher(zhandle_t *zh, int type, 
        int state, const char *path,void *watcherCtx){
    // 子节点发生变化（用于client  zoo_get_child 会设下这个监视器
    // 用于监视服务实例的变化
    if(type == ZOO_CHILD_EVENT){
        // 判断是否是服务变化
        std::string pathStr = std::string(path);
        if(pathStr.find("/services/") != 0){
            // todo
            return;
        }
        // 获取服务名
        std::string name = pathStr.substr(10);
        String_vector data{};
        // 获取子节点并重新添加监视器
        int flag = zoo_get_children(zh, path, 1, &data);
        if(flag != ZOK){
            if(flag == ZNONODE){
                // todo
                Logger::Error("Zookeeper未发现服务："+name);
                return;
            }else{
                Logger::Error("Zookeeper查找服务 "+name+" 异常，返回："+std::to_string(flag));
                return;
            }
        }
        if(data.count == 0){
            Logger::Info("服务 "+name+" 的实例已全部下线");
        }
        std::vector<ServiceInfo> services{};
        for(int i=0;i<data.count;i++){
            // todo 没有考虑权重
            services.push_back(ServiceInfo(data.data[i]));
        }
        // 获取this 指针
        ZkClient* self = static_cast<ZkClient*>(watcherCtx);
        if(self){
            std::lock_guard<std::mutex> lock(self->servicesMutex_);
            // 更改service info
            self->m_services_info_[name] = std::move(services);
        } else{
            Logger::Error("Zookeeper的wathcer未传入this指针");
            return;
        }
        // 通知服务的更改   todo
        
    } 
    // 连接事件 与服务器失联或重连
    else if(type == ZOO_SESSION_EVENT){
        // todo
    }
}

ZkClient::ZkClient(){
    zh = nullptr;
    setLoadBalancer(new RoundRobin());
}
ZkClient::~ZkClient(){
    if (zh != nullptr) {
        zookeeper_close(zh);  // 关闭ZooKeeper连接
    }
}
void ZkClient::setLoadBalancer(LoadBalancer* lb){
    std::lock_guard<std::mutex> lock(balancerMutex_);
    m_lb_.reset(lb);
}

void ZkClient::start(){
    // todo 配置
    std::string ip = "0.0.0.0";
    std::string port = "2181";
    std::string addr = ip + ":" + port;
    // TODO 回调函数
    zh = zookeeper_init(addr.c_str(), &globalWatcher, 6000, nullptr, this, 0);
    if(zh == nullptr){
        throw std::runtime_error("zookeeper connection failed");   // todo 失败
    }
    Logger::Info("Zookeeper客户端建立完毕");
    int flag = zoo_exists(zh, "/services", 0, nullptr);
    if(flag == ZNONODE){
        createNode("/services", nullptr, 0, 0);
        if(flag == ZOK){  // 创建成功
            // Logger::Trace("节点创建成功");
        }else{
            Logger::Error("zookeeper初始化失败，无法创建services根目录，zookeeper返回："+std::to_string(flag));
        }
    }
}

int ZkClient::createNode(const char* path, const char* value, int valueLen, int flags){
    char path_buff[64]{};
    int path_buff_len = sizeof(path_buff);
    int flag = zoo_exists(zh, path, 0, nullptr);
    // Logger::Trace("节点是否存在:"+std::to_string(flag));
    if(flag == ZNONODE){  // 节点不存在
        flag = zoo_create(zh, path, value, valueLen, &ZOO_OPEN_ACL_UNSAFE, flags, path_buff, path_buff_len);
        // Logger::Trace("创建节点:"+std::to_string(flag));
    }
    return flag;
}

void ZkClient::registerService(std::string service, std::string addr){
    std::string path = "/services/" + service;
    // 服务节点为持久节点，因为服务节点表示服务的名称或分类，一般不会改变
    Logger::Trace("试图创建节点:"+service);
    int flag = createNode(path.c_str(), nullptr, 0, 0);
    if(flag == ZOK){  // 创建成功
        Logger::Trace("zkClient:服务 "+service+" 创建成功");
    }else{
        Logger::Error("zkClient:服务 "+service+" 创建失败，zookeeper返回："+std::to_string(flag));
    }
    // 保存服务器的地址为临时节点
    path+="/"+addr;
    createNode(path.c_str(), nullptr, 0, ZOO_EPHEMERAL); 
    if(flag == ZOK){  // 创建成功
        Logger::Trace("zkClient:节点实例 "+addr+" 注册成功");
    }else{
        Logger::Error("zkClient:节点实例 "+addr+" 注册失败，zookeeper返回："+std::to_string(flag));
    }
}

// 弃用
void ZkClient::registerMethod(std::string service, std::string method, std::string data){
    std::string path = "/" + service + "/" +method;
    createNode(path.c_str(), data.c_str(), data.length(), ZOO_EPHEMERAL);
}

std::string ZkClient::findService(std::string service, bool watcher){
    {
        std::lock_guard<std::mutex> lock(servicesMutex_);
        auto it =m_services_info_.find(service);
        if(it != m_services_info_.end()){
            std::lock_guard<std::mutex> lock1(balancerMutex_);
            return m_lb_->select(it->second).addr;
        }
    }
    
    std::string path = "/services/" + service;
    String_vector services{};
    int flag = zoo_get_children(zh, path.c_str(), watcher, &services);
    if(flag != ZOK){
        if(flag == ZNONODE){
            // todo
            Logger::Error("Zookeeper未发现服务："+service);
            return "";
        }else{
            Logger::Error("Zookeeper查找服务 "+service+" 异常，返回："+std::to_string(flag));
            return "";
        }
    }
    if(services.count == 0){
        Logger::Error("Zookeeper未发现服务 "+service+" 的实例");
        return "";
    }
    {
        std::vector<ServiceInfo> servicesInfo{};
        for(int i=0;i<services.count;i++){
            // todo 没有考虑权重
            servicesInfo.push_back(ServiceInfo(services.data[i]));
        }
        std::string addr;
        {
            std::lock_guard<std::mutex> lock(balancerMutex_);
            addr = m_lb_->select(servicesInfo).addr;
        }
        std::lock_guard<std::mutex> lock(servicesMutex_);
        m_services_info_.insert({service, std::move(servicesInfo)});
        return addr;
    }
}