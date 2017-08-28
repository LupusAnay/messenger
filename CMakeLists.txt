cmake_minimum_required(VERSION 3.8)
project(messenger)

set(CMAKE_CXX_STANDARD 11)

find_package( Boost COMPONENTS filesystem system REQUIRED )
include_directories(${BOOST_INCLUDE_DIRS})

set(SOURCE_FILES_SERVER server/main.cpp)
set(SOURCE_FILES_CLIENT client/main.cpp)

add_executable(messenger_client ${SOURCE_FILES_CLIENT})
add_executable(messenger_server ${SOURCE_FILES_SERVER})

target_link_libraries(messenger_client ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})