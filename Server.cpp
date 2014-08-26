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
    std::cout << "[System] Client connecting.." << std::endl;
    if (!error) {
        new_session->setDispatcher(this->dispatcher_);
        new_session->start();
        new_session = new Session(this->io_service_);
        new_session->session_pool = this->session_pool;
        new_session->session_pool->push_back(new_session);

        this->acceptor_.async_accept(new_session->socket(),
                boost::bind(&Server::handle_accept, this, new_session,
                boost::asio::placeholders::error));

        std::cout << "[System] Client successfully connected" << std::endl;
    } else {
        std::cout << "[System] Client connection failed" << std::endl;
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
    std::cout << "[System] Server successfully started.." << std::endl;
    this->dispatcher_ = dispatcher;
    this->session_pool = new std::vector<Session*>();
    Session* new_session = new Session(io_service_);
    new_session->session_pool = this->session_pool;

    acceptor_.async_accept(new_session->socket(),
            boost::bind(&Server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
}
