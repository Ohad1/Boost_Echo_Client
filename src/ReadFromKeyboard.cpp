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
        while (!_connectionHandler->isShouldTerminate()){
            std::string mystr;
            getline (cin,mystr);
            _connectionHandler->sendLine(mystr); //encode and send
        }
    }
};
