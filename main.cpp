#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Server.h"
#include "Dispatcher.h"


using namespace std;

void setupHandlers(Dispatcher &dispatcher);

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
            //argv[1] = "22";
            return 1;
        }

        Dispatcher dispatcher;
        //Deal with handlers setup only
        setupHandlers(dispatcher);

        boost::asio::io_service io_service;

        Server s(io_service, atoi(argv[1]), &dispatcher);
        io_service.run();

    } catch (std::exception& e) {
        std::cerr << "[System] Exception: " << e.what() << "\n";
    }

    return 0;
}

/**
 * 
 * @param dispatcher
 */
void setupHandlers(Dispatcher &dispatcher) {
    dispatcher.registerHandler("GET", new HandlerBase());
}