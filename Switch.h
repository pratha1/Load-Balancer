/**
 * @file Switch.h
 * @brief Defines the Switch class.
 *
 * The Switch simulates a network router that distributes
 * incoming requests to multiple LoadBalancers based on job type.
 *
 * Routing Policy:
 * - 'P' (Processing) → processing LoadBalancer
 * - 'S' (Streaming) → streaming LoadBalancer
 *
 * This implements the bonus objective of concurrent
 * load balancers with job separation.
 */

#ifndef SWITCH_H
#define SWITCH_H

#include "LoadBalancer.h"

/**
 * @class Switch
 * @brief Routes requests between multiple LoadBalancers.
 *
 * The Switch:
 * - Generates random traffic
 * - Creates burst traffic
 * - Distributes requests by type
 * - Runs simulation over time
 */
class Switch {
private:
    LoadBalancer* processingLB;
    LoadBalancer* streamingLB;
    int initialServers;

public:
    /**
     * @brief Constructs the Switch with a given number of servers.
     * 
     * @param servers Initial number of servers per load balancer.
     */
    Switch(int servers);

    /**
     * @brief Destructor.
     * Cleans up dynamically allocated load balancers.
     */
    ~Switch();

    /**
     * @brief Runs the full simulation.
     * 
     * @param duration Number of clock cycles to simulate.
     */
    void run(int duration);
};

#endif