#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <string>
class TCPClient{
public:
    TCPClient();
    TCPClient(const std::string& ip, const std::string& port);
    // virtual void connect();
    virtual void disconnect();
    virtual void sendMessage(const std::string& header, const std::string& body);
    virtual void sendMessage(const std::string& header, const std::string& body, uint32_t id, const std::function<void()>& cb);
};
#endif TCP_CLIENT_H  // TCP_CLIENT_H