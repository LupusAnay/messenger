/*
 * This is messenger's server code
 * Using boost::asio and boost::system
 * Waiting for connection from clients
 * Create thread for every client and receive message to destination user
 */

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

int main()
{
    cout << "It's server" << endl;
    return 0;
}