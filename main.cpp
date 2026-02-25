#include <iostream>
#include "Switch.h"

int main() {
    int servers, time;

    std::cout << "Servers: ";
    std::cin >> servers;

    std::cout << "Simulation Time: ";
    std::cin >> time;

    Switch networkSwitch(servers);
    networkSwitch.run(time);

    return 0;
}