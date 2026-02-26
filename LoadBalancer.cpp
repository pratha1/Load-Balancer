/**
 * @file LoadBalancer
 * @brief Simulates a scalable web load balancer.
 *
 * Responsibilities:
 * - Maintain FIFO request queue
 * - Assign requests to available servers
 * - Process clock cycles
 * - Dynamically scale server pool
 * - Log scaling and firewall events
 * - Provide statistical summary
 *
 * Scaling Policy:
 * - Scale up when queue > UPPER_THRESHOLD × server_count
 * - Scale down when queue < LOWER_THRESHOLD × server_count
 * - Enforce cooldown period between scaling events
 *
 * Firewall:
 * - Blocks private network ranges (192.168.x.x, 10.x.x.x)
 */

#include "LoadBalancer.h"
#include "Config.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

/**
 * @brief Constructs a LoadBalancer with an initial number of servers.
 * 
 * @param serverCount Number of servers to initialize.
 * @param logName Name of the log file for scaling and firewall events.
 */
LoadBalancer::LoadBalancer(int serverCount, std::string logName)
    : totalRequests(0), blockedRequests(0), cooldownTimer(0) {

    logFile.open(logName);

    for (int i = 0; i < serverCount; i++)
        servers.push_back(new WebServer(i));

    srand(time(0));
}

/**
 * @brief Destructor.
 * 
 * Cleans up dynamically allocated servers and closes the log file.
 */
LoadBalancer::~LoadBalancer() {
    for (auto s : servers)
        delete s;
    logFile.close();
}

/**
 * @brief Generates a random IPv4 address.
 * 
 * @return Randomly generated IP address string.
 */
std::string LoadBalancer::randomIP() {
    return std::to_string(rand()%256)+"."+
           std::to_string(rand()%256)+"."+
           std::to_string(rand()%256)+"."+
           std::to_string(rand()%256);
}

/**
 * @brief Checks whether an IP address should be blocked.
 * 
 * Blocks private network ranges:
 * - 192.168.x.x
 * - 10.x.x.x
 * 
 * @param ip IP address to check.
 * @return True if blocked, false otherwise.
 */
bool LoadBalancer::isBlocked(const std::string& ip) {
    if (ip.rfind("192.168", 0) == 0) return true;
    if (ip.rfind("10.", 0) == 0) return true;
    return false;
}

/**
 * @brief Adds a request to the queue if not blocked by firewall.
 * 
 * If blocked, increments blocked request counter and logs the event.
 * Otherwise, pushes request into FIFO queue.
 * 
 * @param req Incoming request.
 */
void LoadBalancer::addRequest(const Request& req) {
    if (isBlocked(req.ipIn)) {
        blockedRequests++;
        logFile << "Blocked IP: " << req.ipIn << "\n";
        return;
    }
    requestQueue.push(req);
    totalRequests++;
}

/**
 * @brief Assigns queued requests to available idle servers.
 * 
 * Each idle server receives one request from the front of the queue.
 */
void LoadBalancer::assignRequests() {
    for (auto s : servers) {
        if (!s->isBusy() && !requestQueue.empty()) {
            s->assignRequest(requestQueue.front());
            requestQueue.pop();
        }
    }
}

/**
 * @brief Advances processing on all servers by one cycle.
 * 
 * Each server reduces remaining processing time of its active request.
 */
void LoadBalancer::processServers() {
    for (auto s : servers)
        s->processCycle();
}

/**
 * @brief Dynamically adjusts server pool size based on queue load.
 * 
 * Scaling rules:
 * - Scale up if queue size exceeds UPPER_THRESHOLD × server_count
 * - Scale down if queue size drops below LOWER_THRESHOLD × server_count
 * - Respect cooldown period between scaling events
 */
void LoadBalancer::scale() {
    if (cooldownTimer > 0) {
        cooldownTimer--;
        return;
    }

    int size = requestQueue.size();
    int serverCount = servers.size();

    if (size > Config::UPPER_THRESHOLD * serverCount) {
        servers.push_back(new WebServer(serverCount));
        std::cout << GREEN << "Scaling Up\n" << RESET;
        logFile << "Scaling Up\n";
        cooldownTimer = Config::SCALING_COOLDOWN;
    }
    else if (size < Config::LOWER_THRESHOLD * serverCount && serverCount > 1) {
        delete servers.back();
        servers.pop_back();
        std::cout << YELLOW << "Scaling Down\n" << RESET;
        logFile << "Scaling Down\n";
        cooldownTimer = Config::SCALING_COOLDOWN;
    }
}

/**
 * @brief Runs the load balancer simulation for a given duration.
 * 
 * Each cycle:
 * - Assign requests to servers
 * - Process active requests
 * - Apply scaling policy
 * 
 * @param duration Number of clock cycles to simulate.
 */
void LoadBalancer::run(int duration) {
    for (int t = 0; t < duration; t++) {
        assignRequests();
        processServers();
        scale();
    }
}

/**
 * @brief Prints final simulation statistics.
 * 
 * Outputs:
 * - Total accepted requests
 * - Total blocked requests
 * - Final server count
 * - Per-server processed request totals
 */
void LoadBalancer::printSummary() {
    std::cout << "\nTotal Requests: " << totalRequests << "\n";
    std::cout << "Blocked Requests: " << blockedRequests << "\n";
    std::cout << "Final Servers: " << servers.size() << "\n";

    for (size_t i = 0; i < servers.size(); i++)
        std::cout << "Server " << i << " processed "
                  << servers[i]->getTotalProcessed() << " requests\n";

    // to log summary 
    logFile << "\n--- Summary ---\n";
    logFile << "Total Requests: " << totalRequests << "\n";
    logFile << "Blocked Requests: " << blockedRequests << "\n";
    logFile << "Final Servers: " << servers.size() << "\n";
    for (size_t i = 0; i < servers.size(); i++)
        logFile << "Server " << i << " processed "
                << servers[i]->getTotalProcessed() << " requests\n";
}