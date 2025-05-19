#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H
#include "LoadBalancer.h"
#include <atomic>

class RoundRobin: public LoadBalancer{
public:
    ServiceInfo select(std::vector<ServiceInfo>& services)override{
        if(services.empty()) return ServiceInfo{};
        uint64_t i = counter.fetch_add(1);    // fetch_add返回的是add前的旧值
        return services[i % services.size()];
    }

private:
    std::atomic<uint64_t> counter{0};
};

#endif  // ROUND_ROBIN_H