#include "RpcApplication.h"
#include "RpcConfig.h"


void RpcApplication::init(std::string configPath){
    // 初始化日志
    Logger::init();
    //  加载配置文件
    RpcConfig::loadFromFile(configPath);

}