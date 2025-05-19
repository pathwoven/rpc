#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <string>
#include "ServiceInfo.h"


class LoadBalancer{
public:
    virtual ~LoadBalancer()=default;
    virtual ServiceInfo select(std::vector<ServiceInfo>& services)=0;
};
#endif  // LOAD_BALANCER_H