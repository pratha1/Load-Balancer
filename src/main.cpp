#include <iostream>
#include "LoadBalancer.h"

int main() {
    int servers, time;

    std::cout << "Servers: ";
    std::cin >> servers;

    std::cout << "Simulation Time: ";
    std::cin >> time;

    LoadBalancer lb(servers, 50);
    lb.run(time);

    return 0;
}