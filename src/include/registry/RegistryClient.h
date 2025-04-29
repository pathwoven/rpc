#ifndef REGISTER_CENTER_H
#define REGISTER_CENTER_H
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include "google/protobuf/service.h"
class RegistryCli{
public:
    virtual void registerService(std::string service, std::string addr);
    virtual void registerMethod(std::string service, std::string method, std::string data="");
    virtual std::string findService(std::string service);
    virtual void start();
private:
};
#endif REGISTER_CENTER_H  // REGISTER_CENTER_H