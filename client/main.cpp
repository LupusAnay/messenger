//
// Created by LupusAnay on 25.08.17.
//
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "client_hdr.h"


/*void recv_msg(socket_ptr socket) {
    char buf[1024];
    size_t bytes = read(*socket, buffer(buf, sizeof(buf)));
    string message(buf, bytes - 1);
    cout << message << endl;
}

void send_msg(socket_ptr socket){
    char buf[1024];
}

void connect_handler(const boost::system::error_code & ec, socket_ptr socket) {
    if(ec.value() != 0){
        cout << "Something wrong with socket connection. Exit" << endl;
        return;
    }

    boost::thread recv(boost::bind(&recv_msg, socket));
    boost::thread send(boost::bind(&send_msg, socket));
    recv.join();
    send.join();
}

int main() {
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
    socket_ptr sock(new ip::tcp::socket(service));
    sock->async_connect(ep, boost::bind(&connect_handler, boost::asio::placeholders::error, sock));
    service.run();
    return 0;
}*/

void connectHandler(const boost::system::error_code & ec){

}

void recvHandler(){

}

void sendHandler(){

}

void read_message(char* msg){

}

int main(){
    io_service service;

    char recv_message[MSG_SIZE];
    char send_message[MSG_SIZE];

    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
    socket_ptr sock(new ip::tcp::socket(service));
    return 0;
}