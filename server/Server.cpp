//
// Created by lupusanay on 13.09.17.
//

#include "Server.h"

Server::Server(unsigned short port) {
    io_service service;
    ip::tcp::endpoint ep(ip::tcp::v4(), port);
    ip::tcp::acceptor acc(service, ep);

    while (acc.is_open()) {
        socket_ptr socket(new ip::tcp::socket(service));
        acc.accept(*socket);
        connections.push_back(new Connection(socket, this));
    }
}

Connection *Server::getConnectionByID(string username) {
    for (auto &connection : connections) {
        if(connection->getUsername() == username) {
            cout << "Client " << username << " founded" << endl;
            return connection;
        }
    }
    cout << "Cant find client " << username << endl;
    //TODO THERE IS NO SUCH USERNAME
}
