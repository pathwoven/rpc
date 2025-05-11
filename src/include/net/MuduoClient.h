#ifndef MUDUO_CLIENT_H
#define MUDUO_CLIENT_H
#include "TCPClient.h"
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <functional>
#include "RpcHeader.pb.h"

class MuduoClient: public TCPClient{
public:
    static void init();   // 必须只执行一次，线程不安全
    // void connect();
    void disconnect()override;
    void sendMessage(const std::string& header, const std::string& body)override;

    //void setConnectionCb();
    void setMessageCb(std::function<void(std::string&, std::string&)>&);

    MuduoClient(const std::string& ip, const std::string& port);
private:
    std::string ip_;
    std::string port_;
    static muduo::net::EventLoop eventLoop_;
    muduo::net::TcpClient client_;
    muduo::net::TcpConnectionPtr conn_;

    std::function<void(std::string&, std::string&)> msgCb_;
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp timestamp);
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
};
#endif MUDUO_CLIENT_H // MUDUO_CLIENT_H