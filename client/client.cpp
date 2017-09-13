//
// Created by LupusAnay on 25.08.17.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/archive_exception.hpp>
#include "../ChatMessage.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void send_func(const socket_ptr &socket, const string &username) {
    ChatMessage message;
    message.source = username;
    while(socket->is_open()) {
        cout << "Who do you want to send a message to: ";
        getline(cin, message.destination);
        cout << "Message: ";
        getline(cin, message.text);

        boost::asio::streambuf buf;
        ostream os( &buf );
        boost::archive::text_oarchive ar(os);
        ar & message;

        const size_t header = buf.size();
        cout << "The message size is " << header << " bytes" << endl;
        vector<const_buffer> buffers;
        buffers.push_back(buffer(&header, sizeof(header)));
        buffers.push_back(buf.data());

        write(*socket, buffers);
    }
}

void read_func(const socket_ptr &socket) {
    while(socket->is_open()) {
        size_t header;
        read(*socket, buffer(&header, sizeof(header)));

        boost::asio::streambuf buf;
        const size_t rc = read(*socket, buf.prepare(header));
        buf.commit(header);

        istream is(&buf);
        boost::archive::text_iarchive ar(is);
        ChatMessage msg;
        ar & msg;
        cout << "Message from: " << msg.source << endl;
        cout << "Text: " << msg.text << endl;
    }
}


void start_session(const string &host, const string &service, const string &username) {
    io_service io_serv;
    ip::tcp::resolver resolver(io_serv);
    ip::tcp::resolver::query query(host, service);
    ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    ip::tcp::endpoint endpoint = *endpoint_iterator;

    socket_ptr socket(new ip::tcp::socket(io_serv));
    boost::system::error_code error;

    cout << "Trying connect to the server: " << endpoint.address() << ":" << endpoint.port() << endl;
    socket->connect(endpoint, error);
    if(error.value() != 0) {
        cerr << "An error occurred while connecting to the server: " << error.message() << endl;
        return;
    }
    else {
        socket->send(buffer(username));
        boost::thread reader(boost::bind(read_func, socket));
        boost::thread sender(boost::bind(send_func, socket, username));
        reader.join();
        sender.join();
    }
}

int main(int argc, char *argv[]) {
    try {
        if(argc != 4) {
            cerr << "Usage: client <host> <port> <username>" << endl;
            return 2;
        }
        start_session(argv[1], argv[2], argv[3]);
    }
    catch (exception &ex) {
        cerr << ex.what() << endl;
        return 1;
    }
}