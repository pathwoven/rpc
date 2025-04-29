#include "ServerStub.h"

void ServerStub::saveServiceInfo(google::protobuf::Service* service){
    // 记录服务信息
    ServiceInfo serviceInfo;
    serviceInfo.service = service;
    
    const google::protobuf::ServiceDescriptor* serviceDescr = service->GetDescriptor();
    // 遍历服务的方法，记录方法名与描述符的映射
    for(int i=0; i<serviceDescr->method_count(); i++){
        const google::protobuf::MethodDescriptor* methodDescr = serviceDescr->method(i);
        serviceInfo.methodMap.emplace(methodDescr->name(), methodDescr);
    }

    // 保存
    this->serviceMap.emplace(serviceDescr->name(), serviceInfo);
}

void ServerStub::registerAllService(std::string ip, int port){
    // 服务端地址
    std::string addr =  ip+":"+std::to_string(port);
    // 连接注册中心
    std::unique_ptr<RegistryCli> RegistryCli = std::make_unique<ZkClient>();
    RegistryCli->start();
    for(auto it = serviceMap.begin();it!=serviceMap.end();it++){
        std::string serviceName = it->first;
        RegistryCli->registerService(serviceName, addr);   // 注册服务
        // for(auto m_it = it->second.methodMap.begin();m_it!=it->second.methodMap.end();m_it++){
        //     RegistryCli->registerMethod(serviceName, m_it->first, addr);  // 注册方法
        // }
    }
}

// 启动节点
void ServerStub::run(){
    // todo 修改为从配置文件读入
    std::string ip = "127.0.0.1";
    int port = 8085;
    std::string name = "Server";

    std::unique_ptr<TCPServer> tcpServer = std::make_unique<MuduoServer>();

    tcpServer->bindListen(ip, port, name);
    tcpServer->setThreadNum(4);

    registerAllService(ip, port);

    tcpServer->run();
}