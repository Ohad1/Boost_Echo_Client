#include <iostream>
#include <boost/thread.hpp>
#include "../include/connectionHandler.h"
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

class ReadFromKeyboard {
private:
    ConnectionHandler *_connectionHandler;

public:
    ReadFromKeyboard(ConnectionHandler *connectionHandler) : _connectionHandler(connectionHandler) {
    }

    void run() {
        while (_connectionHandler->getTerminate() == 0){
            std::string mystr;
            getline (cin,mystr);
            _connectionHandler->sendLine(mystr); //encode and send
            if(mystr=="LOGOUT") {
                while (1) {
                    // ACK
                    if (_connectionHandler->getTerminate() == 1) {
                        break;
                    }
                        // ERROR
                    else if (_connectionHandler->getTerminate() == -1) {
                        _connectionHandler->setTerminate(0);
                        break;
                    }
                }
            }
        }
    }
};
