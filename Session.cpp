#include "Session.h"

/**
 * Session class is for handling service IO
 * @return 
 */

/**
 * This method returns session's socket
 * @return 
 */
tcp::socket& Session::socket() {
    return socket_;
}

/**
 * 
 * @param io_service
 */
Session::Session(boost::asio::io_service& io_service) : socket_(io_service) {

};

/**
 * start(() function begins async reading on connected client
 */
void Session::start() {
    this->socket_.async_read_some(boost::asio::buffer(this->data_, max_length),
            boost::bind(&Session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

/**
 * Handle_read is a callback for some shizzle.. yo
 * @param error
 * @param bytes_transferred
 */
void Session::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {

    if ((boost::asio::error::eof == error) ||
            (boost::asio::error::connection_reset == error)) {
        // this->session_pool_.
        std::cout << "[System] Client Disconnected." << std::endl;

        //Check if pointer is valid
        if (this->session_pool) {
            //Remove current session from pool when client disconnects.
            std::vector<Session*>::iterator iter = this->session_pool->begin();
            for (iter; iter != this->session_pool->end(); ++iter) {
                if (this == (*iter)) {
                    std::cout << "[System] Removed client from session pool." << std::endl;
                    this->session_pool->erase(iter);
                }
            }

        }
    }

    if (!error) {
        //Pass message to dispatcher for parsing and dispatching with handler
        std::string result;

        Message msg;
        msg.message = this->data_;
        msg.result = &result;
        msg.self = this;
        msg.session_pool = this->session_pool;

        memset(this->data_, 0, sizeof (this->data_));
        // this->dispatcher_->handle(message, &result, this, this->session_pool);
        this->dispatcher_->handle(&msg);

        boost::asio::async_write(this->socket_,
                boost::asio::buffer(result.c_str(), result.length()),
                boost::bind(&Session::handle_write, this,
                boost::asio::placeholders::error));
    } else {
        delete this;
    }
}

/**
 * Handles write action. 
 * @param error
 */
void Session::handle_write(const boost::system::error_code& error) {
    if (!error) {
        this->socket_.async_read_some(boost::asio::buffer(this->data_, max_length),
                boost::bind(&Session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    } else {
        delete this;
    }
}

/**
 * 
 * @param dispatcher
 */
void Session::setDispatcher(Dispatcher* dispatcher) {
    this->dispatcher_ = dispatcher;
}

