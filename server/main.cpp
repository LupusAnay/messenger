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
    if(argc != 2) {
        cerr << "Usage: <port>" << endl;
        return 2;
    }
    else {
        Server server(static_cast<unsigned short>(stoi(argv[1])));
    }
}

/*
void client_session(const socket_ptr &socket) {
    while(socket->is_open()) {
        try {
            cout << "Client connected: " << socket->remote_endpoint() << endl;
            size_t header;
            read(*socket, buffer(&header, sizeof(header)));

            cout << "Body is " << header << " bytes" << endl;

            boost::asio::streambuf buf;
            const size_t rc = read(*socket, buf.prepare(header));
            buf.commit(header);

            cout << "Read " << rc << " bytes" << endl;

            istream is(&buf);
            boost::archive::text_iarchive ar(is);
            ChatMessage msg;
            ar & msg;
            cout << "Message from: " << msg.source << endl;
            cout << "Text: " << msg.text << endl;
        }
        catch (boost::system::system_error&) {
            cerr << "Client has closed the connection" << endl;
            return;
        }
    }
}

int main() {
    io_service service;
    ip::tcp::endpoint ep(ip::tcp::v4(), 1488);
    ip::tcp::acceptor acc(service, ep);

    while (acc.is_open()) {
        socket_ptr socket(new ip::tcp::socket(service));
        acc.accept(*socket);
        boost::thread(boost::bind(client_session, socket));
    }
}
*/