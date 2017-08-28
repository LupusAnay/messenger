/*
 * This is messenger's client code
 * Using boost::asio and boost::system
 * Connecting to server
 *
 * 1st thread(may be main):
 *     Waiting for input message
 *     Send message to server
 *     Destination user determined in message
 *
 * 2nd thread:
 *     Waiting a message from server
 *     If received, then print it
 *     Source user name determined in message
 *
 * OR
 *
 * Main thread:
 *     Waiting for input message
 *     Join thread that send message
 *         Send message
 *         Return
 *
 * 2nd thread:
 *     Waiting a message from server
 *     If received, then print it
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>

/*using namespace std;
using namespace boost::asio;

struct Message{
    string message;
    string destination;
};

class Session{
protected:
    Message message;

public:
    Message getMessage()
    {
        return message;
    }
};

class UserSession : public Session{
public:
    void startSession(){

    }
};

static class NetSession : public Session{

private:

    static void startSession(){
        io_service service;
        ip::tcp::socket sock(service);
        ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), 2001);
        sock.async_connect(ep, boost::bind(connect_handler, sock));
        service.run();
    }

public:
    NetSession(){

    }

};

int main()
{
    NetSession netSession();
    return 0;
}*/
