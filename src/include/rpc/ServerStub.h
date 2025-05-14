#ifndef SERVER_STUB_H
#define SERVER_STUB_H
#include "google/protobuf/service.h"
#include "google/protobuf/descriptor.h"
#include "RpcHeader.pb.h"
#include "MuduoServer.h"
#include "ZkClient.h"
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
	std::unordered_map<std::string, ServiceInfo> serviceMap_;

	void onMessage(const std::string& header, const std::string& msg, void* cxt);

	std::function<void(std::string&, std::string&, void*)> sendCb_;
	struct cbCtx{
		google::protobuf::Message* response;
		std::string& header;
		void* cxt;
		cbCtx(google::protobuf::Message* m, std::string& h, void* c):response(m), header(h), cxt(c){}
	};
	void SendMessage(cbCtx* ctx);
};
#endif    // SERVER_STUB_H