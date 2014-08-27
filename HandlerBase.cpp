#include "HandlerBase.h"
#include "Session.h"

/**
 * @author Lauri Orgla 
 */
HandlerBase::HandlerBase() {
}

/**
 * @author Lauri Orgla
 * @param orig
 */
HandlerBase::HandlerBase(const HandlerBase& orig) {
}

/**
 * @author Lauri Orgla
 */
HandlerBase::~HandlerBase() {
}

/**
 * @example orx@OrX:~$ echo -e "get clients\n" | nc 127.0.0.1 22
CONNECTED CLIENTS: 18
 * 
 * @author Lauri Orgla
 * @param message
 * @param result
 */
void HandlerBase::run(Message *msg) {
    std::cout << "[Handler: GET] Input: " << msg->message << std::endl;
    char buffer[256];
    std::cout << msg->message << std::endl;
    if (msg->message == "clients") {
        snprintf(buffer, sizeof (buffer), "CONNECTED CLIENTS: %i\n", msg->session_pool->size() - 1); //exclude current connection
    } else {
        snprintf(buffer, sizeof (buffer), "[Handler: GET] Message received: %s\n", msg->message.c_str());
    }
    //  msg->self->socket().close();

    *msg->result = buffer;
}
