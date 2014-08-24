/* 
 * File:   Dispatcher.h
 * Author: orx
 *
 * Created on August 24, 2014, 2:01 PM
 */

#ifndef DISPATCHER_H
#define	DISPATCHER_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "HandlerBase.h"

class Dispatcher {
public:
    Dispatcher();
    Dispatcher(const Dispatcher& orig);
    virtual ~Dispatcher();
    void registerHandler(std::string name, HandlerBase *handler);
    void handle(std::string message, std::string *result);
private:
    void parseMessage(std::string input, std::string &action, std::string &body);
    std::map <std::string, class HandlerBase *> handlers;
};

#endif	/* DISPATCHER_H */

