#include "ZkClient.h"
#include "Logger.h"
#include <vector>


void globalWatcher(zhandle_t *zh, int type, 
        int state, const char *path,void *watcherCtx){
    
}

ZkClient::ZkClient(){
    zh = nullptr;
}
ZkClient::~ZkClient(){
    if (zh != nullptr) {
        zookeeper_close(zh);  // 关闭ZooKeeper连接
    }
}
void ZkClient::start(){
    // todo 配置
    std::string ip = "127.0.0.1";
    std::string port = "2181";
    std::string addr = ip + ":" + port;
    // TODO 回调函数
    zh = zookeeper_init(addr.c_str(), &globalWatcher, 6000, nullptr, nullptr, 0);
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
    // todo 负载均衡
    return services.data[0];
}