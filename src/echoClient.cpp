#include <stdlib.h>
#include <connectionHandler.h>
#include <thread>
#include "ReadFromSocket.cpp"
#include "ReadFromKeyboard.cpp"
/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    //after we initialize the connection handler we will start the 2 threads
    ReadFromKeyboard task1(&connectionHandler);
    ReadFromSocket task2(&connectionHandler);
    std::thread th1(&ReadFromKeyboard::run, &task1);
    std::thread th2(&ReadFromSocket::run, &task2);
    th1.join();
    th2.join();
    return 0;
}
