/**
 * @file Switch.cpp
 * @brief Implements the Switch class.
 */

#include "Switch.h"
#include "Config.h"
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructs a Switch with two LoadBalancers.
 * 
 * One load balancer handles processing requests.
 * One load balancer handles streaming requests.
 * 
 * @param servers Initial number of servers per load balancer.
 */
Switch::Switch(int servers) {
    processingLB = new LoadBalancer(servers, "processing_log.txt");
    streamingLB = new LoadBalancer(servers, "streaming_log.txt");

    initialServers = servers; 
    srand(time(0));
}

/**
 * @brief Destructor.
 * 
 * Frees dynamically allocated LoadBalancers.
 */
Switch::~Switch() {
    delete processingLB;
    delete streamingLB;
}

/**
 * @brief Runs the full simulation for a specified duration.
 * 
 * Simulation Steps:
 * 1. Generate an initial queue load
 * 2. For each clock cycle:
 *    - Generate burst traffic
 *    - Route requests based on job type
 *    - Advance both load balancers
 * 3. Print final summaries
 * 
 * @param duration Number of clock cycles to simulate.
 */
void Switch::run(int duration) {

    // Initial queue fill
    int initialLoad = initialServers * Config::INITIAL_QUEUE_MULTIPLIER;

    for (int i = 0; i < initialLoad; i++) {

        std::string ipIn =
            std::to_string(rand()%256)+"."+
            std::to_string(rand()%256)+"."+
            std::to_string(rand()%256)+"."+
            std::to_string(rand()%256);

        std::string ipOut = ipIn;
        char type = (rand()%2 == 0) ? 'P' : 'S';

        Request r(ipIn, ipOut,
                  rand()%Config::MAX_PROCESS_TIME+1,
                  type);

        if (type == 'P')
            processingLB->addRequest(r);
        else
            streamingLB->addRequest(r);
    }

    // Main simulation loop
    for (int t = 0; t < duration; t++) {

        int burst = rand() % 5 + 1;

        for (int i = 0; i < burst; i++) {

            std::string ipIn =
                std::to_string(rand()%256)+"."+
                std::to_string(rand()%256)+"."+
                std::to_string(rand()%256)+"."+
                std::to_string(rand()%256);

            std::string ipOut = ipIn;
            char type = (rand()%2 == 0) ? 'P' : 'S';

            Request r(ipIn, ipOut,
                      rand()%Config::MAX_PROCESS_TIME+1,
                      type);

            if (type == 'P')
                processingLB->addRequest(r);
            else
                streamingLB->addRequest(r);
        }

        processingLB->run(1);
        streamingLB->run(1);
    }

    // Print final results
    processingLB->printSummary();
    streamingLB->printSummary();
}