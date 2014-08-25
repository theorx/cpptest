/* 
 * File:   Server.h
 * Author: root
 *
 * Created on August 22, 2014, 7:54 PM
 */

#ifndef SESSION_H
#define	SESSION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Dispatcher.h"
using boost::asio::ip::tcp;

class Session {
public:

    Session(boost::asio::io_service& io_service);
    tcp::socket& socket();
    void start();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code& error);
    void setDispatcher(Dispatcher *dispatcher);
    void setSessionPool(std::vector<Session*> *pool);

private:
    tcp::socket socket_;

    enum {
        max_length = 1024
    };
    char data_[max_length];
    Dispatcher *dispatcher_;
    std::vector<Session *> *session_pool_;
};

#endif	/* SERVER_H */

