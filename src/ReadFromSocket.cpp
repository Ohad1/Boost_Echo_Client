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
            if(_connectionHandler->getLine(answer)) {
                printf ("%s \n", "in if");
                printf("%s\n",answer.c_str()); // get the line from the socket after decode and print
            }
//            std::string answer;
//            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
//            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
//            if (!_connectionHandler->getLine(answer)) {
//                std::cout << "Disconnected. Exiting...\n" << std::endl;
//                break;
//            }
//
//            int len = answer.length();
//            std::cout << "len: " << len << " " << std::endl << std::endl;
//
//            // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
//            // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
//            answer.resize(len-1);
//            std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
//            if (answer == "bye") {
//                std::cout << "Exiting...\n" << std::endl;
//                break;
//            }
        }
    }
};