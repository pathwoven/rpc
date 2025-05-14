#include "RpcApplication.h"
#include "Caculator.pb.h"

#include <thread>
#include <vector>

void sendRequest(int threadId, std::atomic<uint32_t>& successCount, std::atomic<uint32_t>& failedCount){
    
}

int main(int argc, char** argv){
    // 初始化框架
    RpcApplication::init(argc, argv);

    // 设置并发的参数
    const int threadNum = 10;
    const int requestNum = 10;

    std::vector<std::thread> threads;
    std::atomic<uint32_t> successCount(0);
    std::atomic<uint32_t> failedCount(0); 

    // 记录测试开始
    auto start = std::chrono::high_resolution_clock::now();

    for(int i=0; i<threadNum; i++){
        threads.emplace_back([i, &successCount, &failedCount, requestNum](){
            for(int j=0; j<requestNum; j++){
                sendRequest(i, successCount, failedCount);
            }
        });
    }

    // 等待线程执行完毕
    for(auto &t: threads){
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = start - end;

    // 输出统计结果
    Logger::Info("Total requests: " + std::to_string(threadNum * requestNum));  
    Logger::Info("Success count: " + std::to_string(successCount));  
    Logger::Info("Fail count: " + std::to_string(failedCount));  
    Logger::Info("Elapsed time: " + std::to_string(elapsed.count()) + " seconds");  
    Logger::Info("QPS: " + std::to_string((threadNum * requestNum) / elapsed.count()));  
}