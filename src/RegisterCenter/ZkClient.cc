#include "ZkClient.h"

ZkClient::ZkClient(){
    zh = nullptr;
}
void ZkClient::start(){
    // todo 配置
    std::string ip = "127.0.0.1";
    std::string port = "8086";
    std::string addr = ip + ":" + port;
    // TODO 回调函数
    zh = zookeeper_init(addr.c_str(), nullptr, 6000, nullptr, nullptr, 0);
    if(zh == nullptr){
        throw std::runtime_error("zookeeper connection failed");   // todo 失败
    }
}

void ZkClient::createNode(const char* path, const char* value, int valueLen, int state){
    int flag = zoo_exists(zh, path, 0, nullptr);
    if(flag == ZNONODE){  // 节点不存在
        flag = zoo_create(zh, path, value, valueLen, &ZOO_OPEN_ACL_UNSAFE, state, nullptr, 0);
        if(flag == ZOK){  // 创建成功
            // todo
        }else{

        }
    }
}

void ZkClient::registerService(std::string service){
    std::string path = "/" + service;
    // 服务节点为持久节点，因为服务节点表示服务的名称或分类，一般不会改变
    createNode(path.c_str(), nullptr, 0, 0);
}

void ZkClient::registerMethod(std::string service, std::string method, std::string data){
    std::string path = "/" + service + "/" +method;
    createNode(path.c_str(), data.c_str(), data.length(), ZOO_EPHEMERAL);
}