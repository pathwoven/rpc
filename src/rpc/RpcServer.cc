#include "RpcServer.h"
#include "Logger.h"

void RpcServer::saveServiceInfo(google::protobuf::Service* service){
    // 记录服务信息
    ServiceInfo serviceInfo;
    serviceInfo.service = service;
    
    const google::protobuf::ServiceDescriptor* serviceDescr = service->GetDescriptor();
    // 遍历服务的方法，记录方法名与描述符的映射
    for(int i=0; i<serviceDescr->method_count(); i++){
        const google::protobuf::MethodDescriptor* methodDescr = serviceDescr->method(i);
        serviceInfo.methodMap.emplace(std::string(methodDescr->name()), methodDescr);
    }

    // 保存
    this->serviceMap_.emplace(std::string(serviceDescr->name()), serviceInfo);
}

void RpcServer::registerAllService(std::string ip, int port){
    // 服务端地址
    std::string addr =  ip+":"+std::to_string(port);
    // 连接注册中心
    std::unique_ptr<RegistryClient> RegistryCliPtr = std::make_unique<ZkClient>();
    RegistryCliPtr->start();
    for(auto it = serviceMap_.begin();it!=serviceMap_.end();it++){
        std::string serviceName = it->first;
        RegistryCliPtr->registerService(serviceName, addr);   // 注册服务
        // for(auto m_it = it->second.methodMap.begin();m_it!=it->second.methodMap.end();m_it++){
        //     RegistryCliPtr->registerMethod(serviceName, m_it->first, addr);  // 注册方法
        // }
    }
}

void RpcServer::onMessage(const std::string& header, const std::string& msg, void* cxt){
    RpcHeader::RequestHeader rpcHeader;
    google::protobuf::Service* service;
    const google::protobuf::MethodDescriptor* mDesc;
    uint32_t reqId;
    // 读取头部
    if(rpcHeader.ParseFromString(header)){
        auto sm = serviceMap_.find(rpcHeader.service());
        if(sm==serviceMap_.end()){
            // todo 错误
        }
        service = sm->second.service;
        auto mm = sm->second.methodMap.find(rpcHeader.method());
        if(mm==sm->second.methodMap.end()){
            // todo
        }
        mDesc = mm->second;
        reqId = rpcHeader.id();
    }else{
        // todo 参数错误
    }
    // 读取rpc体
    google::protobuf::Message* request = service->GetRequestPrototype(mDesc).New();
    if(!request->ParseFromString(msg)){
    // todo error
    }
    google::protobuf::Message* response = service->GetResponsePrototype(mDesc).New();
    // 封装头部
    RpcHeader::ResponseHeader resHeader;
    resHeader.set_id(reqId);
    std::string resHeader_str;
    if(!resHeader.SerializeToString(&resHeader_str)){
        // todo error
    }
    // 定义回调函数   todo delete new
    RpcServer::cbCtx* cbCtx = new RpcServer::cbCtx(response, resHeader_str, cxt);
    google::protobuf::Closure* done = google::protobuf::NewCallback(this, &RpcServer::SendMessage, cbCtx);
    service->CallMethod(mDesc, nullptr, request, response, done);
    
}

void RpcServer::SendMessage(cbCtx* cxt){
    std::string response;
    if(!cxt->response->SerializeToString(&response)){
        // todo
    }
    sendCb_(cxt->header, response, cxt->cxt);
}

// 启动节点
void RpcServer::run(){
    // todo 修改为从配置文件读入
    std::string ip = "0.0.0.0";
    int port = 8085;
    std::string name = "Server";

    registerAllService(ip, port);
    Logger::Trace("服务注册完毕");

    // 启动tcp服务
    std::unique_ptr<MuduoServer> tcpServer = std::make_unique<MuduoServer>();

    tcpServer->bindListen(ip, port, name);
    tcpServer->setThreadNum(4);

    // 设置回调函数
    tcpServer->setMessCallback(std::bind(&RpcServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    tcpServer->setSendCallback(sendCb_);

    Logger::Info("服务器"+ip+":"+std::to_string(port)+"开始运行");
    tcpServer->run();
}