//
// Created by lupusanay on 13.09.17.
//

#ifndef MESSENGER_CONNECTION_H
#define MESSENGER_CONNECTION_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <utility>
#include "../ChatMessage.h"

using namespace std;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

class Server;

class Connection {

public:
    Connection(socket_ptr sock, Server *serv);
    string getUsername();
    void sendMessage(ChatMessage message);
    ~Connection();

private:
    Server *server;
    socket_ptr socket;
    string username;
    void startRead();
};

#endif //MESSENGER_CONNECTION_H
