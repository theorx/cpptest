#ifndef DISPATCHER_H
#define	DISPATCHER_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include <string.h>
#include "HandlerBase.h"
#include "Message.h"

class HandlerBase;
struct Message;

class Dispatcher {
public:
    Dispatcher();
    Dispatcher(const Dispatcher& orig);
    virtual ~Dispatcher();
    void registerHandler(std::string name, HandlerBase *handler);
    void handle(Message *msg);
private:
    void parseMessage(std::string input, std::string &action, std::string &body);
    std::map <std::string, class HandlerBase *> handlers;
};

#endif	/* DISPATCHER_H */

