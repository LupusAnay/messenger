//
// Created by LupusAnay on 25.08.17.
//

/*
 * This is messenger's server code
 * Using boost::asio and boost::system
 * Waiting for connection from clients
 * Create thread for every client and receive message to destination user
 */

#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include "Server.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Checking for arguments
    if(argc != 2) {
        cerr << "Usage: messenger_server <port>" << endl;
        return 2;
    }
    else {
        Server server(static_cast<unsigned short>(stoi(argv[1])));
    }
}
