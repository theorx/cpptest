#include "Server.h"

/**
 * snippet:
 *        new_session->start();
        char buffer[] = "";
        new_session->socket().send(boost::asio::buffer(buffer, sizeof (buffer)));
 */

/**
 * @author Lauri Orgla
 * 
 * @param new_session
 * @param error
 */
void Server::handle_accept(Session* new_session, const boost::system::error_code& error) {

    std::cout << "Incoming connection.." << std::endl;
    if (!error) {
        new_session->setDispatcher(this->dispatcher_);
        new_session->start();
        new_session = new Session(this->io_service_);
        this->acceptor_.async_accept(new_session->socket(),
                boost::bind(&Server::handle_accept, this, new_session,
                boost::asio::placeholders::error));

        std::cout << "Accepted.." << std::endl;
    } else {
        std::cout << "Failed.." << std::endl;
        delete new_session;
    }
}

/**
 * Service constuctor. Should be moved to initialize method.
 * 
 * @author Lauri Orgla
 * 
 * @param io_service
 * @param port
 */
Server::Server(boost::asio::io_service& io_service, short port, Dispatcher *dispatcher) : io_service_(io_service),
acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {

    this->dispatcher_ = dispatcher;
    Session* new_session = new Session(io_service_);

    acceptor_.async_accept(new_session->socket(),
            boost::bind(&Server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
}
