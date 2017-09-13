//
// Created by lupusanay on 13.09.17.
//

#include "Connection.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <utility>
#include "Server.h"

Connection::Connection(socket_ptr sock, Server *serv) {
    socket = std::move(sock);
    server = serv;
    auto *buf = new char[32];
    socket->read_some(buffer(buf, 32));
    username = string(buf);
    cout << "Client connected: " << socket->remote_endpoint() << endl;
    cout << "Username: " << username << endl;
    boost::thread read_thread(boost::bind(&Connection::startRead, this));
}

void Connection::startRead() {
    while(socket->is_open()) {
        try {
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
            Connection *dest = server->getConnectionByID(msg.destination);
            dest->sendMessage(msg);
        }
        catch (boost::system::system_error&) {
            cerr << "Client has close the connection" << endl;
            socket->close();
            break;
        }
    }
    cout << "Reading messages from " << username << " stopped" << endl;
}

void Connection::sendMessage(ChatMessage message) {
    boost::asio::streambuf buf;
    ostream os(&buf);
    boost::archive::text_oarchive ar(os);
    ar & message;

    const size_t header = buf.size();

    vector<const_buffer> buffers;
    buffers.push_back(buffer(&header, sizeof(header)));
    buffers.push_back(buf.data());

    write(*socket, buffers);
}

string Connection::getUsername() {
    return username;
}
