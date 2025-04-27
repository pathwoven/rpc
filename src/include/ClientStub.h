#ifndef CLIENT_STUB_H
#define CLIENT_STUB_H
#include <string>
class ClientStub {
public: 
    void connect(std::string ip, int port);
    void findService();
private:

};
#endif CLIENT_STUB_H  // CLIENT_STUB_H