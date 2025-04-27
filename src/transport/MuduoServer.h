#ifndef MUDUO_SERVER_H
#define MUDUO_SERVER_H
#include "TCPServer.h"
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
class MuduoServer: public TCPServer{
public:
    void BindListen(std::string ip, int port, std::string name="") override;
    void SetConnCallback(void (*OnConnection())) override;
    void SetMessCallback(void (*OnMessage())) override;
    void SetThreadNum(int num) override;
    void Run() override;
private:
    muduo::net::EventLoop eventLoop;
    std::shared_ptr<muduo::net::TcpServer> server;
    void OnConnection(const muduo::net::TcpConnectionPtr& conn);
    void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp receiveTime);
    
};
#endif MUDUO_SERVER_H