#include "RpcConfig.h"
#include <yaml-cpp/yaml.h>

void RpcConfig::loadFromFile(std::string path){
    YAML::Node config = YAML::LoadFile(path);
    std::vector<std::string> zookeeperNodes = config["zookeeper"]["nodes"].as<std::vector<std::string>>();
    for(int i=0; i<zookeeperNodes.size()-1; i++){
        zookeeperAddr+=zookeeperNodes[i]+",";
    }
    zookeeperAddr+=zookeeperNodes[zookeeperNodes.size()-1];
}