#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include<string>
class TCPClient{
public:
    TCPClient(std::string ip, int port);
    void connect();
    void setMessageCallback();
private:
    uint32_t requestId;
    int sk;
};
#endif TCP_CLIENT_H  // TCP_CLIENT_H