#include "RpcConfig.h"
#include <yaml-cpp/yaml.h>
#include<Logger.h>

void RpcConfig::loadFromFile(std::string path){
    Logger::Info(path);
    try{
        YAML::Node config = YAML::LoadFile(path);
        // zookeeper
        std::vector<std::string> zookeeperNodes = config["zookeeper"]["nodes"].as<std::vector<std::string>>();
        for(size_t i=0; i<zookeeperNodes.size()-1; i++){
            zookeeperAddr+=zookeeperNodes[i]+",";
        }
        zookeeperAddr+=zookeeperNodes[zookeeperNodes.size()-1];
        // server
        if(config["server"]["addr"]){
            RpcConfig::serverAddr = config["server"]["addr"].as<std::string>();
        }
    }catch(const std::exception& e){
        Logger::Error(e.what());
    }
    
}

std::string RpcConfig::zookeeperAddr = "";
std::string RpcConfig::serverAddr  = "";