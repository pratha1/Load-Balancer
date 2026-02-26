/**
 * @file Config.h
 * @brief Global configuration settings for the Load Balancer simulation.
 */

#ifndef CONFIG_H
#define CONFIG_H

/**
 * @namespace Config
 * @brief Holds all tunable parameters for the simulation.
 */
namespace Config {
    const int LOWER_THRESHOLD = 50;
    const int UPPER_THRESHOLD = 80;
    const int INITIAL_QUEUE_MULTIPLIER = 100;
    const int MAX_PROCESS_TIME = 10;
    const int SCALING_COOLDOWN = 50; // wait n cycles before next scaling
}

#endif