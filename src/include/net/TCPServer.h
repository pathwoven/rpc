#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <string>
#include <functional>
class TCPServer{
public:
    virtual void bindListen(std::string ip, int port, std::string name="")=0;
    virtual void setConnCallback(void (*onConnection()))=0;
    virtual void setMessCallback(std::function<void(std::string&, std::string&, void* cxt)>)=0;
    virtual void setThreadNum(int n)=0;
    virtual void run()=0;
};
#endif   // TCP_SERVER_H