#ifndef MUDUO_SERVER_H
#define MUDUO_SERVER_H
#include "TCPServer.h"
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
class MuduoServer: public TCPServer{
public:
    void bindListen(std::string ip, int port, std::string name="") override;
    void setConnCallback(void (*onConnection())) override;
    void setMessCallback(std::function<void(std::string&, std::string&, void* cxt)> cb);
    void setSendCallback(std::function<void(std::string&,std::string&,void*)>& sendCb);
    void setThreadNum(int num) override;
    void run() override;
private:
    muduo::net::EventLoop eventLoop_;
    std::shared_ptr<muduo::net::TcpServer> server_;
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp receiveTime);
    std::function<void(std::string&, std::string&, void*)> messCb_; 
    void SendMessage(std::string& header, std::string& message, const muduo::net::TcpConnectionPtr& conn);

};
#endif // MUDUO_SERVER_H