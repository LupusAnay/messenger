//
// Created by root on 09.09.17.
//

#ifndef MESSENGER_CHATMESSAGE_H
#define MESSENGER_CHATMESSAGE_H

#include <iostream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

struct ChatMessage {
    std::string destination;
    std::string source;
    std::string text;

    template<class Archive> void serialize(Archive &ar, const unsigned int version)
    {
        ar & destination;
        ar & source;
        ar & text;
    }
};

#endif //MESSENGER_CHATMESSAGE_H
