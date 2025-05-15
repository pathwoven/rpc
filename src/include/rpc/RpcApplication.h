// 负责初始化操作
#ifndef RPC_APPLICATION_H
#define RPC_APPLICATION_H
#define DEBUG   // todo

#include "Logger.h"

class RpcApplication{
public:
    static void init(int argc, char** argv);
};
#endif   // RPC_APPLICATION_H