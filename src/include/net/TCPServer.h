#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <string>
class TCPServer{
public:
    virtual void bindListen(std::string ip, int port, std::string name="");
    virtual void setConnCallback(void (*OnConnection()));
    virtual void setMessCallback(void (*OnMessage()));
    virtual void setThreadNum(int n);
    virtual void run();
};
#endif TCP_SERVER_H  // TCP_SERVER_H