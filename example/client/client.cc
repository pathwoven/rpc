#include "RpcApplication.h"
#include "Caculator.pb.h"

#include <thread>
#include <vector>

void SendRequest(int threadId, std::atomic<uint32_t>& successCount, std::atomic<uint32_t>& failedCount){
    
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

    }
}