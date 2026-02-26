/**
 * @file WebServer.cpp
 * @brief Implements the WebServer class.
 */

#include "WebServer.h"

/**
 * @brief Constructs a WebServer with a unique ID.
 * 
 * @param id Unique identifier for the server.
 */
WebServer::WebServer(int id)
    : id(id), busy(false), remainingTime(0), totalProcessed(0) {}

/**
 * @brief Checks whether the server is currently processing a request.
 * 
 * @return True if server is busy, false otherwise.
 */
bool WebServer::isBusy() const {
    return busy;
}

/**
 * @brief Assigns a request to the server.
 * 
 * The server becomes busy and sets its remaining processing time
 * based on the request's process time.
 * 
 * @param req Request to process.
 */
void WebServer::assignRequest(const Request& req) {
    busy = true;
    remainingTime = req.processTime;
}

/**
 * @brief Advances the server by one clock cycle.
 * 
 * Decrements remaining processing time.
 * When processing completes:
 * - Server becomes idle
 * - Total processed counter increments
 */
void WebServer::processCycle() {
    if (busy) {
        remainingTime--;
        if (remainingTime <= 0) {
            busy = false;
            totalProcessed++;
        }
    }
}

/**
 * @brief Returns the total number of completed requests.
 * 
 * @return Number of processed requests.
 */
int WebServer::getTotalProcessed() const {
    return totalProcessed;
}