/**
 * @file WebServer.h
 * @brief Defines the WebServer class.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Simulates a web server that processes requests.
 */
class WebServer {
private:
    int id;
    bool busy;
    int remainingTime;
    int totalProcessed;

public:
    WebServer(int id);

    bool isBusy() const;
    void assignRequest(const Request& req);
    void processCycle();
    int getTotalProcessed() const;
};

#endif