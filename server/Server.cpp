//
// Created by lupusanay on 13.09.17.
//

#include "Server.h"

Server::Server(unsigned short port) {
    io_service service;
    ip::tcp::endpoint ep(ip::tcp::v4(), port);
    ip::tcp::acceptor acc(service, ep);

    while (acc.is_open()) {
        // Create connection and push it into connections vector
        socket_ptr socket(new ip::tcp::socket(service));
        acc.accept(*socket);
        connections.push_back(new Connection(socket, this));
    }
}

Connection *Server::getConnectionByID(string username) {
    // Iterate all connections and looking for <username> connection
    for (auto &connection : connections) {
        if(connection->getUsername() == username) {
            cout << "Client " << username << " founded" << endl;
            return connection;
        }
    }
    cout << "Cant find client " << username << endl;
}

void Server::destroyConnection(Connection *connect) {
    for (auto it = connections.begin(); it != connections.end(); ++it) {
        if(*it == connect) {
            connections.erase(it);
            return;
        }
    }
}
