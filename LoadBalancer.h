/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include <fstream>
#include "WebServer.h"

/**
 * @class LoadBalancer
 * @brief Manages request queue, servers, scaling, and firewall.
 */
class LoadBalancer {
private:
    std::queue<Request> requestQueue;
    std::vector<WebServer*> servers;

    int totalRequests;
    int blockedRequests;
    int cooldownTimer;

    std::ofstream logFile;

    std::string randomIP();
    bool isBlocked(const std::string& ip);

    void scale();
    void assignRequests();
    void processServers();

public:
    LoadBalancer(int serverCount, std::string logName);
    ~LoadBalancer();

    void addRequest(const Request& req);
    void run(int duration);
    void printSummary();
};

#endif