//
// Created by LupusAnay on 29.08.17.
//

#include "client_hdr.h"

#ifndef MESSENGER_SOCKET_H
#define MESSENGER_SOCKET_H

#endif //MESSENGER_SOCKET_H

class Socket{

public:
    Socket(const ip::address &ep_adr, ep_port port);
    void send(char msg[MSG_SIZE]);
    chat_message* read();
    void close_connection();

private:
    io_service service;
    ip::tcp::socket asio_socket;
    ip::tcp::endpoint ep;

    chat_message message[MSG_SIZE];
};