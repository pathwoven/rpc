#include "Calculator.pb.h"
#include "RpcApplication.h"
#include "RpcServer.h"

class CalculatorService:public MyService::Calculator{
public:
    void Add(google::protobuf::RpcController* controller, const MyService::AddRequest* request,
        MyService::AddResponse* response, google::protobuf::Closure* done)override{
        // 获取请求
        int a = request->a();
        int b = request->b();

        // 调用本地方法
        int ret = Add(a, b);

        // 写入响应
        response->set_result(ret);

        // 完成，调用回调
        done->Run();
    }
private:
    // 本地方法
    int Add(int a, int b){
        return a + b;
    }
};

int main(int argc, char** argv){
    // 初始化
    if(argc == 0) RpcApplication::init("../config.yml");
    else RpcApplication::init(argv[0]);

    RpcServer stub;
    
    // 注册服务
    stub.saveServiceInfo(new CalculatorService());
    Logger::Trace("本地服务注册完毕");

    // 运行服务器
    stub.run();

    return 0;
}