#include <connectionHandler.h>
 
using boost::asio::ip::tcp;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
 
ConnectionHandler::ConnectionHandler(string host, short port): host_(host), port_(port), io_service_(),
socket_(io_service_), shouldTerminate(false){}
    
ConnectionHandler::~ConnectionHandler() {
    close();
}
 
bool ConnectionHandler::connect() {
    std::cout << "Starting connect to " 
        << host_ << ":" << port_ << std::endl;
    try {
		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
		boost::system::error_code error;
		socket_.connect(endpoint, error);
		if (error)
			throw boost::system::system_error(error);



    }
    catch (std::exception& e) {
        std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}
 
bool ConnectionHandler::getBytes(char bytes[], unsigned int bytesToRead) {
    size_t tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToRead > tmp ) {
			tmp += socket_.read_some(boost::asio::buffer(bytes+tmp, bytesToRead-tmp), error);			
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

// good
bool ConnectionHandler::sendBytes(const char bytes[], int bytesToWrite) {
    int tmp = 0;
	boost::system::error_code error;
    try {
        while (!error && bytesToWrite > tmp ) {
			tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
        }
		if(error)
			throw boost::system::system_error(error);
    } catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }
    return true;
}

// good
bool ConnectionHandler::getLine(std::string& line) {
    return getFrameAscii(line, '\n');
}
// good
bool ConnectionHandler::sendLine(std::string& line) {
    return sendFrameAscii(line, '\n');
}
 
bool ConnectionHandler::getFrameAscii(std::string& frame, char delimiter) {
    char ch;
    char serverToClientOpcodeArray[2];
    char messageOpcodeArray[2];
    short serverToClientOpcode;
    short messageOpcode;
    try {
        getBytes(&ch, 1);
        serverToClientOpcodeArray[0] = ch;
        getBytes(&ch, 1);
        serverToClientOpcodeArray[1] = ch;
        serverToClientOpcode = bytesToShort(serverToClientOpcodeArray);
        if (serverToClientOpcode==9) {
            getBytes(&ch, 1);
            frame.append(1, ch);
            frame.append(" ");
            do{
                getBytes(&ch, 1);
                frame.append(1, ch);
            }while ('\0' != ch);
            frame.append(" ");
            do{
                getBytes(&ch, 1);
                frame.append(1, ch);
            }while ('\0' != ch);
            return true;
        }
        else {
            getBytes(&ch, 1);
            messageOpcodeArray[0] = ch;
            getBytes(&ch, 1);
            messageOpcodeArray[0] = ch;
            messageOpcode = bytesToShort(messageOpcodeArray);
            if (serverToClientOpcode==11) {
                frame.append("ERROR " + std::to_string(messageOpcode));
                return true;
            }
            else if (serverToClientOpcode==10) {
                if (messageOpcode==3) {
                    frame.append("ACK " + std::to_string(messageOpcode));
                    return true;
                }
                else if (messageOpcode==4 | messageOpcode==7) {
                    char numOfUsersArray[2];
                    getBytes(&ch, 1);
                    numOfUsersArray[0] = ch;
                    getBytes(&ch, 1);
                    numOfUsersArray[0] = ch;
                    short numOfUsers = bytesToShort(numOfUsersArray);
                    frame.append(std::to_string(10) + " " + std::to_string(messageOpcode) + " " + std::to_string(numOfUsers));
                    //string username;
                    for (int i = 0; i < numOfUsers; i++) {
                        do{
                            getBytes(&ch, 1);
                            frame.append(1, ch);
                        }while ('\0' != ch);
                        if (i!=numOfUsers-1) {
                            frame.append(" ");
                        }
                    }
                }
                else if (messageOpcode==8) {
                    char numOfPostsArray[2];
                    getBytes(&ch, 1);
                    numOfPostsArray[0] = ch;
                    getBytes(&ch, 1);
                    numOfPostsArray[0] = ch;
                    short numOfPosts = bytesToShort(numOfPostsArray);
                    char numOfFollowersArray[2];
                    getBytes(&ch, 1);
                    numOfFollowersArray[0] = ch;
                    getBytes(&ch, 1);
                    numOfFollowersArray[0] = ch;
                    short numOfFollowers = bytesToShort(numOfFollowersArray);
                    char numOfFollowingsArray[2];
                    getBytes(&ch, 1);
                    numOfFollowingsArray[0] = ch;
                    getBytes(&ch, 1);
                    numOfFollowingsArray[0] = ch;
                    short numOfFollowing = bytesToShort(numOfFollowingsArray);
                    frame.append(std::to_string(10) + " " +
                    std::to_string(numOfPosts) + " " +
                    std::to_string(numOfFollowers) + " " +
                    std::to_string(numOfFollowing));
                    return true;
                }
            }
        }
        return false;
    }
    catch (std::exception& e) {
        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
        return false;
    }


    // Stop when we encounter the null character. 
    // Notice that the null character is not appended to the frame string.
//    try {
//		do{
//			getBytes(&ch, 1);
//            frame.append(1, ch);
//        }while (delimiter != ch);
//    } catch (std::exception& e) {
//        std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
//        return false;
//    }
//    return true;
}
 
bool ConnectionHandler::sendFrameAscii(const std::string& frame, char delimiter) {
	bool result=sendBytes(frame.c_str(),frame.length());
	if(!result) return false;
	return sendBytes(&delimiter,1);
}
 
// Close down the connection properly.
void ConnectionHandler::close() {
    try{
        socket_.close();
    } catch (...) {
        std::cout << "closing failed: connection already closed" << std::endl;
    }
}

bool ConnectionHandler::isShouldTerminate() const {
    return shouldTerminate;
}

void ConnectionHandler::setShouldTerminate(bool shouldTerminate) {
    ConnectionHandler::shouldTerminate = shouldTerminate;
}

short ConnectionHandler::bytesToShort(char* bytesArr)
{
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void ConnectionHandler::shortToBytes(short num, char* bytesArr)
{
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

