/**
 * @file Request.h
 * @brief Defines the Request structure used in the load balancer simulation.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a single client request.
 *
 * Contains:
 * - Source IP address
 * - Destination IP address
 * - Processing time
 * - Job type ('P' or 'S')
 */
struct Request {
    std::string ipIn;
    std::string ipOut;
    int processTime;
    char jobType;

    Request(std::string in, std::string out, int time, char type)
        : ipIn(in), ipOut(out), processTime(time), jobType(type) {}
};

#endif