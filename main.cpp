#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Server.h"
#include "Dispatcher.h"

/**
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: server <port>\n";
            std::cout << "Setting default port to 34\n";
            argv[1] = "34";
            // return 1;
        }
        Dispatcher dispatcher;
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