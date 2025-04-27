#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <string>
class TCPServer{
public:
    virtual void BindListen(std::string ip, int port, std::string name="");
    virtual void SetConnCallback(void (*OnConnection()));
    virtual void SetMessCallback(void (*OnMessage()));
    virtual void SetThreadNum(int n);
    virtual void Run();
};
#endif TCP_SERVER_H  // TCP_SERVER_H