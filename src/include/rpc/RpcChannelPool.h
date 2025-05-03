#ifndef RPC_CHANNEL_POOL_H
#define RPC_CHANNEL_POOL_H
#include "RpcChannel.h"
class RpcChannelPool{
public:
    RpcChannel* pickChannel();   // 从池中选出一个channel
};
#endif RPC_CHANNEL_POOL_H  // RPC_CHANNEL_POOL_H