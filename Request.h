#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request {
    std::string ipIn;
    std::string ipOut;
    int processTime;
    char jobType;

    Request(std::string in, std::string out, int time, char type) : ipIn(in), ipOut(out), processTime(time), jobType(type){}
};

#endif