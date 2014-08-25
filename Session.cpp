#include "Session.h"
#include "Dispatcher.h"
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
        std::cout << "Disconnected.." << std::endl;

        //todo handle disconnected client

        //   std::vector<Session*> pool = *session_pool_;

        //   std::vector<Session*>::iterator iter;
        /*    for(iter = pool.begin(); iter != pool.end();){
                std::cout << " Item.. " << std::endl;
            }*/

    }

    char buffer[bytes_transferred / sizeof (char)];
    strncpy(buffer, this->data_, bytes_transferred);

    if (!error) {
        std::string result;
        std::string message = this->data_;
        this->dispatcher_->handle(message, &result);
        this->data_[0] = '\0';
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

/**
 * 
 * @param pool
 */
void Session::setSessionPool(std::vector<Session*>* pool) {
    this->session_pool_ = pool;
}