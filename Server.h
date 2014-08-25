#ifndef SERVER_H
#define	SERVER_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Session.h"
#include "Dispatcher.h"
#include <vector>


using boost::asio::ip::tcp;

class Server {
public:

    Server(boost::asio::io_service& io_service, short port, Dispatcher *dispatcher);
    void handle_accept(Session* new_session, const boost::system::error_code& error);
    void setDispatcher(Dispatcher *d);
private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    Dispatcher *dispatcher_;
    std::vector< Session* > sessions_;
};

#endif	/* SERVER_H */

