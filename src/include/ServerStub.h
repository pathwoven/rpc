#ifndef SERVER_STUB_H
#define SERVER_STUB_H
#include "google/protobuf/service.h"
class ServerStub {
public:
	// 注册方法，保存映射
	void RegisterService(google::protobuf::Service* service);
	// 启动服务器节点，开始提供rpc服务
	void Run();
private:
};
#endif SERVER_STUB_H   // SERVER_STUB_H