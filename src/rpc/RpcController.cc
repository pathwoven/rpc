#include "RpcController.h"

// client的调用的方法----------------------------
// 重置状态以供复用新的call，不能在rpc运行中时调用
void RpcController::Reset(){

}
// 当call结束时，返回true如果失败了
bool RpcController::Failed() const{
    return false;
} 
// 当failed为真，返回错误描述
std::string RpcController::ErrorText() const {
    return "";
}
// 尝试终止调用
void RpcController::StartCancel(){

}

// server的调用方法------------------------------
// 使failed()返回true
void RpcController::SetFailed(const std::string& reason){

}
// 检查客户端是否已终止调用（即使server要cancel，仍然要执行done回调)
bool RpcController::IsCanceled() const{

    return false;
}
// 注册一个回调函数，当cancel时会被调用
void RpcController::NotifyOnCancel(google::protobuf::Closure* callback){

}