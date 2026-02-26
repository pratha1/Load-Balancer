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
 * @brief Manages request queue, servers, scaling, firewall, and logging.
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
class LoadBalancer {
private:
    std::queue<Request>      requestQueue;   ///< FIFO queue of pending requests
    std::vector<WebServer*>  servers;        ///< Heap-allocated pool of active servers

    int totalRequests;      ///< Count of accepted (non-blocked) requests
    int blockedRequests;    ///< Count of firewall-rejected requests
    int cooldownTimer;      ///< Ticks remaining before next scale event is allowed
    int startingQueueSize;  ///< Queue size captured after initial fill

    std::ofstream logFile;  ///< Log stream for blocked IPs, scaling events, and summary

    std::string randomIP();
    bool isBlocked(const std::string& ip);

    void scale();
    void assignRequests();
    void processServers();

public:
    /**
     * @brief Constructs a LoadBalancer with an initial number of servers.
     * @param serverCount Number of servers to initialize.
     * @param logName Name of the log file for scaling and firewall events.
     */
    LoadBalancer(int serverCount, std::string logName);

    /**
     * @brief Destructor. Cleans up dynamically allocated servers and closes log file.
     */
    ~LoadBalancer();

    /**
     * @brief Adds a request to the queue if not blocked by firewall.
     * @param req Incoming request.
     */
    void addRequest(const Request& req);

    /**
     * @brief Runs the load balancer simulation for a given duration.
     * @param duration Number of clock cycles to simulate.
     */
    void run(int duration);

    /**
     * @brief Captures the current queue size as the starting queue size.
     *
     * Called by Switch after the initial queue fill so the log can
     * report how large the queue was before any processing began.
     */
    void setStartingQueueSize();

    /**
     * @brief Prints and logs final simulation statistics.
     *
     * Outputs to both stdout and the log file:
     * - Starting and ending queue size
     * - Task time range
     * - Total accepted and blocked requests
     * - Final server count and per-server totals
     * - Total completed requests
     * - Firewall block rate
     */
    void printSummary();
};

#endif