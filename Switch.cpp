#include "Switch.h"
#include <iostream>

Switch::Switch(int servers) {
    processingLB = new LoadBalancer(servers, 50);
    streamingLB = new LoadBalancer(servers, 50);
}

Switch::~Switch() {
    delete processingLB;
    delete streamingLB;
}

void Switch::run(int duration) {
    std::cout << "Running Processing Load Balancer\n";
    processingLB->run(duration);

    std::cout << "\nRunning Streaming Load Balancer\n";
    streamingLB->run(duration);
}