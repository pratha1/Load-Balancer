#include "WebServer.h"

WebServer::WebServer(int id){
    this->id = id;
    busy = false;
    remainingTime = 0;
    totalProcessed = 0;
}

bool WebServer::isBusy() const{
    return busy;
}

void WebServer::assignRequest(const Request& req){
    busy = true;
    remainingTime = req.processTime;
}

void WebServer::processRequest(){
    if (busy){
        remainingTime--;
        if (remainingTime <= 0){
            busy = false;
            totalProcessed++;
        }        
    }
}

int WebServer::getTotalProcessed() const{
    return totalProcessed;
}