#ifndef DISPATCHER_H
#define	DISPATCHER_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>
#include <string.h>
#include "HandlerBase.h"

class Dispatcher {
public:
    Dispatcher();
    Dispatcher(const Dispatcher& orig);
    virtual ~Dispatcher();
    void registerHandler(std::string name, HandlerBase *handler);
    void handle(std::string message, std::string *result, Session* self, std::vector<Session*> *session_pool);
private:
    void parseMessage(std::string input, std::string &action, std::string &body);
    std::map <std::string, class HandlerBase *> handlers;
};

#endif	/* DISPATCHER_H */

