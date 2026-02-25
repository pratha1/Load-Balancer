#ifndef SWITCH_H
#define SWITCH_H

#include "LoadBalancer.h"

class Switch {
private:
    LoadBalancer* processingLB;
    LoadBalancer* streamingLB;

public:
    Switch(int servers);
    ~Switch();

    void run(int duration);
};

#endif