#ifndef SERVER_STUB_H
#define SERVER_STUB_H
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "transport/MuduoServer.h"
#include "zookeeper/zookeeper.h"
#include <map>
class ServerStub {
public:
	// 保存该服务的信息
	void saveServiceInfo(google::protobuf::Service* service);
	// 注册服务到注册中心
	void registerAllService();
	// 启动服务器节点，开始提供rpc服务
	void run();
private:
	// 存储单个服务内部方法名与方法的映射映射的结构
	struct ServiceInfo{
		google::protobuf::Service* service;
		std::unordered_map<std::string, google::protobuf::MethodDescriptor*> methodMap;
	};
	// 存储服务名与服务信息的映射
	std::unordered_map<std::string, ServiceInfo> serviceMap;
};
#endif SERVER_STUB_H   // SERVER_STUB_H