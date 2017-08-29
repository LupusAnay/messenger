//
// Created by LupusAnay on 29.08.17.
//
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#ifndef MESSENGER_CLIENT_HDR_H
#define MESSENGER_CLIENT_HDR_H

#endif //MESSENGER_CLIENT_HDR_H

using namespace boost::asio;
using namespace std;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef u_short ep_port;
typedef char chat_message;

const u_short MSG_SIZE = 1024;