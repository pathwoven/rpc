#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H
#include<queue>

class ConnectionPool{
public:
    void get();
    void free();
};
#endif CONNECTION_POOL_H // CONNECTION_POOL_H