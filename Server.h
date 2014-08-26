#ifndef SERVER_H
#define	SERVER_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <iostream>
#include "Session.h"
#include "Dispatcher.h"

using boost::asio::ip::tcp;

class Server {
public:

    Server(boost::asio::io_service& io_service, short port, Dispatcher *dispatcher);
    void handle_accept(Session* new_session, const boost::system::error_code& error);
    void setDispatcher(Dispatcher *d);
    std::vector<Session*> *session_pool;
private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    Dispatcher *dispatcher_;
};

#endif	/* SERVER_H */

