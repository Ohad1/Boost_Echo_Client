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
            std::cout << "run  ReadFromKeyboard" << std::flush;
            std::string mystr;
            std::cout << "hello1" << std::flush;
            getline (cin,mystr);
            std::cout << "hello2" << std::flush;
            std::cout << "word: " + mystr << std::flush;
            _connectionHandler->sendLine(mystr); //encode and send
        }
    }
};
