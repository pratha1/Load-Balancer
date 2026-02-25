#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include "WebServer.h"

class LoadBalancer {
private:
    std::queue<Request> requestQueue;
    std::vector<WebServer*> servers;

    int totalRequests;
    int blockedRequests;
    int interval;

    std::string randomIP();
    bool blocked(const std::string& ip);

public:
    LoadBalancer(int serverCount, int interval);
    ~LoadBalancer();

    void run(int duration);
};

#endif