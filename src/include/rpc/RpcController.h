#ifndef RPC_CONTROLLER_H
#include "google/protobuf/service.h"
class RpcController: public google::protobuf::RpcController{
public:
    // client的调用的方法----------------------------
    // 重置状态以供复用新的call，不能在rpc运行中时调用
    void Reset()override;
    // 当call结束时，返回true如果失败了
    bool Failed() const override;
    // 当failed为真，返回错误描述
    std::string ErrorText() const override;
    // 尝试终止调用
    void StartCancel() override;

    // server的调用方法------------------------------
    // 使failed()返回true
    void SetFailed(const std::string& reason)override;
    // 检查客户端是否已终止调用（即使server要cancel，仍然要执行done回调)
    bool IsCanceled() const override;
    // 注册一个回调函数，当cancel时会被调用
    void NotifyOnCancel(google::protobuf::Closure* callback)override;
};
#define RPC_CONTROLLER_H
#endif RPC_CONTROLLER_H // RPC_CONTROLLER_H