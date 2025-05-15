#ifndef REGISTER_CENTER_H
#define REGISTER_CENTER_H
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include "google/protobuf/service.h"
class RegistryClient{
public:
    virtual void registerService(std::string service, std::string addr)=0;
    virtual void registerMethod(std::string service, std::string method, std::string data="")=0;
    virtual std::string findService(std::string service, bool watcher=true)=0;
    virtual void start()=0;
private:
};
#endif   // REGISTER_CENTER_H