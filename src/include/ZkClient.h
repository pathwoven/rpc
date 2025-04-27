#ifndef ZK_CLIENT_H
#define ZK_CLIENT_H
#include "RegisterClient.h"
#include "zookeeper/zookeeper.h"
class ZkClient: public RegisterCli{
public:
    ZkClient();
    ~ZkClient();
    void start()override;
    void registerService(google::protobuf::Service* service) override;
    void findService(google::protobuf::Service* service)override;
private:
    zhandle_t* zh;
};
#endif ZK_CLIENT_H  // ZK_CLIENT_H