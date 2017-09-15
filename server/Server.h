//
// Created by lupusanay on 13.09.17.
//

#ifndef MESSENGER_SERVER_H
#define MESSENGER_SERVER_H

#include <vector>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Connection.h"

using namespace std;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;


class Server {

public:
    Connection *getConnectionByID(string username);
    explicit Server(unsigned short port);
    void destroyConnection(Connection *connect);

private:
    vector<Connection *> connections;
};

#endif //MESSENGER_SERVER_H
