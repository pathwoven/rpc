#ifndef MUDUO_CLIENT_H
#define MUDUO_CLIENT_H
#include "TCPClient.h"
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <functional>
#include <mutex>
#include <unordered_map>
#include "RpcHeader.pb.h"

class MuduoClient: public TCPClient{
public:
    static void init();   // 必须只执行一次，线程不安全
    // void connect();
    void disconnect()override;

    void sendMessage(const std::string& header, const std::string& body)override;
    void sendMessage(const std::string& header, const std::string& body, uint32_t id, const std::function<void()>& cb)override;

    //void setConnectionCb();
    void setMessageCb(std::function<void(std::string&, std::string&)>&);

    MuduoClient(const std::string& ip, const std::string& port);
private:
    std::string ip_;
    std::string port_;
    static std::shared_ptr<muduo::net::EventLoop> eventLoop_;
    muduo::net::TcpClient client_;
    muduo::net::TcpConnectionPtr conn_;

    // 异常恢复  todo
    void handleConnectionError();
    void tryReconnect();   // 重连

    // 请求的回调锁
    std::mutex idMutex_;
    std::unordered_map<uint32_t, std::function<void()>> responseCbMap_;

    std::function<void(std::string&, std::string&)> msgCb_;
    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp timestamp);
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
};
#endif  // MUDUO_CLIENT_H