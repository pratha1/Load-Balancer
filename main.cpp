
/**
 * @file main.cpp
 * @brief Entry point for the Load Balancer simulation.
 *
 * This program simulates a scalable web server load balancing system.
 *
 * User Inputs:
 * - Initial number of servers
 * - Simulation duration (clock cycles)
 *
 * The program then:
 * 1. Creates a Switch object
 * 2. Runs the simulation
 * 3. Outputs final statistics
 */

#include <iostream>
#include "Switch.h"

int main() {

    int servers;
    int simulationTime;

    std::cout << "Servers: ";
    std::cin >> servers;

    std::cout << "Simulation Time: ";
    std::cin >> simulationTime;

    /**
     * Create switch with specified server count.
     * Each LoadBalancer is initialized with this value.
     */
    Switch networkSwitch(servers);

    /**
     * Run full simulation for specified duration.
     */
    networkSwitch.run(simulationTime);

    return 0;
}