#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include<string>
class TCPClient{
public:
    TCPClient(const std::string& ip, const std::string& port);
    void connect();
private:
    std::string ip_;
    std::string port_;
    int sk_;
};
#endif TCP_CLIENT_H  // TCP_CLIENT_H