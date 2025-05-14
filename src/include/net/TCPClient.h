#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <string>
#include <functional>
class TCPClient{
public:
    //TCPClient(){}
    //TCPClient(const std::string& ip, const std::string& port);
    // virtual void connect();
    // note: 假如不在TCP类中实现该函数，记得定义为纯虚函数
    virtual void disconnect()=0;
    virtual void sendMessage(const std::string& header, const std::string& body)=0;
    virtual void sendMessage(const std::string& header, const std::string& body, uint32_t id, const std::function<void()>& cb)=0;
};
#endif   // TCP_CLIENT_H