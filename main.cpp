#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Server.h"
#include "Dispatcher.h"

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }
        Dispatcher dispatcher ;
        dispatcher.registerHandler("GET", new HandlerBase());
        boost::asio::io_service io_service;

        using namespace std; // For atoi.
        Server s(io_service, atoi(argv[1]), &dispatcher);
        
        io_service.run();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}