#include "ZkClient.h"

ZkClient::ZkClient(){
    zh = nullptr;
}
void ZkClient::start(){
    // todo 配置
    std::string ip = "127.0.0.1";
    std::string port = "8086";
    std::string addr = ip + ":" + port;

    
}

void ZkClient::registerService(google::protobuf::Service* service){
    

}