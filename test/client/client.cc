#include "RpcApplication.h"
#include "RpcController.h"
#include "Calculator.pb.h"
#include "RpcClient.h"

#include <thread>
#include <vector>

void sendRequest(RpcClient &rpcClient,int threadId, std::atomic<uint32_t>& successCount, std::atomic<uint32_t>& failedCount){
    // 获取存根
    std::unique_ptr<MyService::Calculator_Stub> stub = rpcClient.getStub<MyService::Calculator_Stub>("Calculator");

    // 设置请求
    MyService::AddRequest req;
    req.set_a(1);
    req.set_b(2);

    // 初始化响应和控制器
    MyService::AddResponse res;
    RpcController controller;

    // 调用
    stub->Add(&controller, &req, &res, nullptr);

    // // 检查结果
    // if(!controller.Failed() && res.result() == 2){
    //     // 调用成功
    //     successCount.fetch_add(1);
    // }else{
    //     failedCount.fetch_add(1);
    // }
}

int main(int argc, char** argv){
    // 初始化框架
    if(argc == 0) RpcApplication::init("../config.yml");
    else RpcApplication::init(argv[0]);
    
    // 初始化客户端
    RpcClient rpcClient;
    Logger::Info("客户端开始运行");

    // 设置并发的参数
    const int threadNum = 100;
    const int requestNum = 100;

    std::vector<std::thread> threads;
    std::atomic<uint32_t> successCount(0);
    std::atomic<uint32_t> failedCount(0); 

    // 记录测试开始
    auto start = std::chrono::high_resolution_clock::now();

    for(int i=0; i<threadNum; i++){
        threads.emplace_back([i, &successCount, &failedCount, requestNum, &rpcClient](){
            for(int j=0; j<requestNum; j++){
                sendRequest(rpcClient,i, successCount, failedCount);
            }
        });
    }

    // 等待线程执行完毕
    for(auto &t: threads){
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // 输出统计结果
    Logger::Info("Total requests: " + std::to_string(threadNum * requestNum));  
    Logger::Info("Success count: " + std::to_string(successCount));  
    Logger::Info("Fail count: " + std::to_string(failedCount));  
    Logger::Info("Elapsed time: " + std::to_string(elapsed.count()) + " seconds");  
    Logger::Info("QPS: " + std::to_string((threadNum * requestNum) / elapsed.count()));  
}