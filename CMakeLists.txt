cmake_minimum_required(VERSION 3.8)
project(messenger)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS filesystem system REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

set(SOURCE_FILES_SERVER
        server/main.cpp
        ChatMessage.h
        server/Server.cpp
        server/Server.h
        server/Connection.cpp
        server/Connection.h)

set(SOURCE_FILES_CLIENT client/client.cpp ChatMessage.h)

add_executable(messenger_client ${SOURCE_FILES_CLIENT})
add_executable(messenger_server ${SOURCE_FILES_SERVER})

target_link_libraries(messenger_client
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        boost_thread
        boost_serialization
        pthread)

target_link_libraries(messenger_server ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} boost_thread boost_serialization)

