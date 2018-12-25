#include <iostream>
#include <boost/thread.hpp>
#include "../include/connectionHandler.h"

class ReadFromKeyboard {
private:
    ConnectionHandler *_connectionHandler;
    boost::mutex *_mutex;

public:
    ReadFromKeyboard(ConnectionHandler *connectionHandler, boost::mutex *mutex) : _connectionHandler(connectionHandler), _mutex(mutex) {
    }

    void run() {
        while (!_connectionHandler->isShouldTerminate()){

            boost::mutex::scoped_lock lock(*_mutex);

        }
    }
};
