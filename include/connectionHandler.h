#ifndef CONNECTION_HANDLER__
#define CONNECTION_HANDLER__
                                           
#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class ConnectionHandler {
private:
	const std::string host_;
	const short port_;
	boost::asio::io_service io_service_;   // Provides core I/O functionality
	tcp::socket socket_;
    int terminate;
public:
    int getTerminate() const;

    void setTerminate(int terminate);

public:
    ConnectionHandler(std::string host, short port);
    virtual ~ConnectionHandler();
 
    // Connect to the remote machine
    bool connect();

    //encode- gets string and parse to byte
    std::vector<char> encode(std::string msg); //todo check *char
 
    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead);
 
	// Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite);
	
    // Read an ascii line from the server
    // Returns false in case connection closed before a newline can be read.
    bool getLine(std::string& line);
	
	// Send an ascii line from the server
    // Returns false in case connection closed before all the data is sent.
    bool sendLine(std::string& line);
 
    // Get Ascii data from the server until the delimiter character
    // Returns false in case connection closed before null can be read.
    bool getFrameAscii(std::string& frame, char delimiter);
 
    // Send a message to the remote host.
    // Returns false in case connection is closed before all the data is sent.
    bool sendFrameAscii(const std::string& frame, char delimiter);
	
    // Close down the connection properly.
    void close();

    std::vector<char> buildLogin(std::string basic_string);

    std::vector<char> buildRegister(std::string basic_string);

    std::vector<char> buildLogout(std::string basic_string);

    std::vector<char> buildFollow(std::string basic_string);

    short bytesToShort(char* bytesArr);

    void shortToBytes(short num, char* bytesArr);


    std::vector<char> buildPost(std::string basic_string);

    std::vector<char> buildPM(std::string basic_string);

    std::vector<char> buildUserList(std::string basic_string);

    std::vector<char> buildSTAT(std::string basic_string);
}; //class ConnectionHandler

#endif