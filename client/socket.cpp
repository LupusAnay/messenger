//
// Created by LupusAnay on 29.08.17.
//

//class Socket is simple wrapper for boost::asio::ip::tcp::socket

#include "client_hdr.h"

class Socket{

public:
    Socket(const ip::address &ep_adr, const ep_port port){
        asio_socket = ip::tcp::socket(service);
        ep = ip::tcp::endpoint(ep_adr, port);
        asio_socket.connect(ep);
    }

    void send(char msg[MSG_SIZE]){
        boost::asio::write(asio_socket, buffer(msg, MSG_SIZE));
    }

    chat_message* read(){
        boost::asio::read(asio_socket, buffer(message, MSG_SIZE));
        return message;
    }

    void close_connection(){
        asio_socket.close();
    }

private:
    io_service service;
    ip::tcp::socket asio_socket = ip::tcp::socket(service);
    ip::tcp::endpoint ep;

    chat_message message[MSG_SIZE];
};
