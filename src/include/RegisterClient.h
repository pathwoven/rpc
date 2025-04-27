#ifndef REGISTER_CENTER_H
#define REGISTER_CENTER_H
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include "google/protobuf/service.h"
class RegisterCli{
public:
    virtual void registerService(google::protobuf::Service* service);
    virtual void findService(google::protobuf::Service* service);
    virtual void start();
private:
};
#endif REGISTER_CENTER_H  // REGISTER_CENTER_H