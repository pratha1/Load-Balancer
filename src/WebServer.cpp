#include "WebServer.h"

WebServer::WebServer(int id){
    this->id = id;
    busy = false;
    remainingTime = 0;
    totalProcessed = 0;
}

bool WebServer::isBusy(){
    return busy;
}

void WebServer::assignRequest(Request req){
    busy = true;
    remainingTime = req.processTime;
}

void WebServer::processCycle(){
    if (busy){
        remainingTime--;
        if (remainingTime <= 0){
            busy = false;
            totalProcessed++;
        }        
    }
}

int WebServer::getTotalProcessed(){
    return totalProcessed;
}