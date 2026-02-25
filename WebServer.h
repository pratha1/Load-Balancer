#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer{
private:
    int id;
    bool busy;
    int remainingTime;
    int totalProcessed;

public:
    WebServer(int id);
    
    bool isBusy() const;
    void assignRequest(const Request& req);
    void processRequest();
    int getTotalProcessed() const;   
};

#endif