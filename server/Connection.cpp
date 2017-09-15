//
// Created by lupusanay on 13.09.17.
//

#include "Connection.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Server.h"

Connection::Connection(socket_ptr sock, Server *serv) {
    socket = std::move(sock);
    server = serv;
    // Reading username
    auto *buf = new char[32];
    socket->read_some(buffer(buf, 32));
    username = string(buf);
    cout << "Client connected: " << socket->remote_endpoint() << endl;
    cout << "Username: " << username << endl;
    // Create thread for reading messages from client
    boost::thread read_thread(boost::bind(&Connection::startRead, this));
}

void Connection::startRead() {
    while(socket->is_open()) {
        try {
            // Reading header
            size_t header;
            read(*socket, buffer(&header, sizeof(header)));
            cout << "Body is " << header << " bytes" << endl;
            // Creating streambuf and reading body
            boost::asio::streambuf buf;
            const size_t rc = read(*socket, buf.prepare(header));
            buf.commit(header);
            cout << "Read " << rc << " bytes" << endl;
            // Deserialize from archive into struct
            istream is(&buf);
            boost::archive:: text_iarchive ar(is);
            ChatMessage msg;
            ar & msg;
            // Looking for destination connected client
            // If founded - send it
            // Else send message to client "server cant find destination
            try {
                Connection *dest = server->getConnectionByID(msg.destination);
                dest->sendMessage(msg);
            }
            catch (boost::system::system_error&) {
                ChatMessage reply;
                reply.destination = username;
                reply.source = "Server";
                reply.text = "There is no such user";
                sendMessage(reply);
            }
        }
        catch (boost::system::system_error&) {
            cerr << "Client " << username << " has close the connection" << endl;
            socket->close();
            break;
        }
    }
    cout << "Reading messages from " << username << " stopped" << endl;
    server->destroyConnection(this);
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

Connection::~Connection() {
    delete &*socket;
    delete server;
    cout << "Destructor for " << username << " connection used" << endl;
}

