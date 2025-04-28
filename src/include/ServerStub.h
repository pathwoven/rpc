#ifndef SERVER_STUB_H
#define SERVER_STUB_H
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "transport/MuduoServer.h"
#include "RegisterCenter/ZkClient.h"
#include <map>
class ServerStub {
public:
	// 保存该服务的信息
	void saveServiceInfo(google::protobuf::Service* service);
	
	// 启动服务器节点，开始提供rpc服务
	void run();
private:
	// 注册所有服务到注册中心  适用于于此前未注册过服务
	void registerAllService(std::string ip, int port);  // 参数为本机地址
	// 存储单个服务内部方法名与方法的映射映射的结构
	struct ServiceInfo{
		google::protobuf::Service* service;
		std::unordered_map<std::string, google::protobuf::MethodDescriptor*> methodMap;
	};
	// 存储服务名与服务信息的映射
	std::unordered_map<std::string, ServiceInfo> serviceMap;
};
#endif SERVER_STUB_H   // SERVER_STUB_H