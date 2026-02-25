#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

LoadBalancer::LoadBalancer(int initialServers, int interval) {
    totalRequests = 0;
    blockedRequests = 0;
    scalingInterval = interval;

    for (int i = 0; i < initialServers; i++)
        servers.push_back(new WebServer(i));

    srand(time(0));

    // Initial requests = 100 per server
    for (int i = 0; i < initialServers * 100; i++) {
        std::string ip = std::to_string(rand()%256)+"."+
                         std::to_string(rand()%256)+"."+
                         std::to_string(rand()%256)+"."+
                         std::to_string(rand()%256);

        if (ip.substr(0,7) != "192.168") {
            requestQueue.push(Request(ip, ip, rand()%10+1, 'P'));
            totalRequests++;
        } else {
            blockedRequests++;
        }
    }
}

LoadBalancer::~LoadBalancer() {
    for (auto s : servers)
        delete s;
}

void LoadBalancer::runSimulation(int duration) {

    for (int t = 0; t < duration; t++) {

        // Random new request
        if (rand()%3 == 0) {
            std::string ip = std::to_string(rand()%256)+"."+
                             std::to_string(rand()%256)+"."+
                             std::to_string(rand()%256)+"."+
                             std::to_string(rand()%256);

            if (ip.substr(0,7) != "192.168") {
                requestQueue.push(Request(ip, ip, rand()%10+1, 'P'));
                totalRequests++;
            } else {
                blockedRequests++;
            }
        }

        // Assign requests to idle servers
        for (auto s : servers) {
            if (!s->isBusy() && !requestQueue.empty()) {
                s->assignRequest(requestQueue.front());
                requestQueue.pop();
            }
        }

        // Process servers
        for (auto s : servers)
            s->processRequest();

        // Scaling check
        if (t % scalingInterval == 0) {
            if (requestQueue.size() > 80 * servers.size()) {
                servers.push_back(new WebServer(servers.size()));
                std::cout << "Scaling Up\n";
            }
            else if (requestQueue.size() < 50 * servers.size() && servers.size() > 1) {
                delete servers.back();
                servers.pop_back();
                std::cout << "Scaling Down\n";
            }
        }
    }

    std::cout << "\nSimulation Complete\n";
    std::cout << "Total Requests: " << totalRequests << "\n";
    std::cout << "Blocked Requests: " << blockedRequests << "\n";
    std::cout << "Final Servers: " << servers.size() << "\n";
}