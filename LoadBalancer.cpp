#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

LoadBalancer::LoadBalancer(int serverCount, int interval) {
    totalRequests = 0;
    blockedRequests = 0;
    this->interval = interval;
    const int LOWER_THRESHOLD = 50;
    const int UPPER_THRESHOLD = 80;

    for (int i = 0; i < serverCount; i++)
        servers.push_back(new WebServer(i));

    srand(time(0));

    // Initial queue = 100 per server
    for (int i = 0; i < serverCount * 100; i++) {
        std::string ip = randomIP();
        if (!blocked(ip)) {
            char type = (rand() % 2 == 0) ? 'P' : 'S';
            requestQueue.push(Request(ip, randomIP(), rand()%10+1, type));
            totalRequests++;
        }
    }
}

LoadBalancer::~LoadBalancer() {
    for (auto s : servers)
        delete s;
}

std::string LoadBalancer::randomIP() {
    return std::to_string(rand()%256)+"."+
           std::to_string(rand()%256)+"."+
           std::to_string(rand()%256)+"."+
           std::to_string(rand()%256);
}

bool LoadBalancer::blocked(const std::string& ip) {
    return ip.substr(0,7) == "192.168";
}

void LoadBalancer::run(int duration) {

    for (int t = 0; t < duration; t++) {

        // Random new request
        if (rand()%3 == 0) {
            std::string ip = randomIP();
            if (!blocked(ip)) {
                char type = (rand() % 2 == 0) ? 'P' : 'S';
                requestQueue.push(Request(ip, randomIP(), rand()%10+1, type));
                totalRequests++;
            } else {
                blockedRequests++;
            }
        }

        // Assign requests
        for (auto s : servers) {
            if (!s->isBusy() && !requestQueue.empty()) {
                s->assignRequest(requestQueue.front());
                requestQueue.pop();
            }
        }

        // Process servers
        for (auto s : servers)
            s->processRequest();

        // Scaling
        if (t % interval == 0) {
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

    std::cout << "\nSimulation Finished\n";
    std::cout << "Total Requests: " << totalRequests << "\n";
    std::cout << "Blocked Requests: " << blockedRequests << "\n";
    std::cout << "Final Servers: " << servers.size() << "\n";
}