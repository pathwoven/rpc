#ifndef RANDOM_BALANCER_H
#define RANDOM_BALANCER_H
#include "LoadBalancer.h"
#include <random>

class RandomBalancer: public LoadBalancer{
public:
    ServiceInfo select(std::vector<ServiceInfo>& services)override{
        if(services.empty()) return ServiceInfo{};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, services.size() - 1);
        return services[dis(gen)];
    }
};
#endif   // RANDOM_BALANCER_H