#ifndef SERVICE_INFO_H
#define SERVICE_INFO_H
#include <string>

struct ServiceInfo{
    std::string addr;
    int weight;
    ServiceInfo(std::string s="", int w=0):addr(s), weight(w){}
};
#endif     // SERVICE_INFO_H