#include <iostream>
#include <boost/thread.hpp>
#include "../include/connectionHandler.h"
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

class ReadFromSocket {
private:
    ConnectionHandler *_connectionHandler;

public:
    ReadFromSocket(ConnectionHandler *connectionHandler) : _connectionHandler(connectionHandler) {
    }

    void run() {
        while (!_connectionHandler->isShouldTerminate()){
            std::cout << "run  ReadFromSocket" << std::endl;
            string answer="";
            if(_connectionHandler->getLine(answer))
                printf("%s\n",answer.c_str()); // get the line from the socket after decode and print
        }
    }
};