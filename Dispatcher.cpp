/* 
 * File:   Dispatcher.cpp
 * Author: orx
 * 
 * Created on August 24, 2014, 2:01 PM
 */

#include "Dispatcher.h"
#include <cstdlib>
#include <string>
#include <string.h>

/**
 * 
 */
Dispatcher::Dispatcher() {
}

/**
 * 
 * @param orig
 */
Dispatcher::Dispatcher(const Dispatcher& orig) {
}

/**
 * 
 */
Dispatcher::~Dispatcher() {
    /**
     * Deletes all
     */
    for (std::map<std::string, class HandlerBase * >::iterator it = this->handlers.begin(); it != this->handlers.end(); ++it) {
        delete it->second;
    }
}

/**
 * 
 * @author Lauri Orgla
 * 
 * @param name
 * @param handler
 */
void Dispatcher::registerHandler(std::string name, HandlerBase* handler) {
    /**Convert name to uppercase*/
    std::locale locale;
    for (std::string::size_type i = 0; i < name.length(); ++i)
        name[i] = std::toupper(name[i], locale);
    /**conversion end*/

    if (handlers.find(name) == handlers.end()) {
        handlers.insert(std::pair<std::string, HandlerBase*>(name, handler));
    } else {
        //deletes handler in case if handler is not added to map
        //Garbage collection.
        delete handler;
        std::cout << "Handler with name " << name << " Is already registered." << std::endl;
    }
}

/**
 * Handle 
 * 
 * @author Lauri Orgla
 * 
 * @param message
 * @param result
 */
void Dispatcher::handle(std::string message, std::string *result) {
    //Remove newline characters
    for (int i = 0; i < message.length(); i++) {
        if (message[i] == '\n') {
            message[i] = ' ';
        }
    }
    std::string body;
    std::string action;
    parseMessage(message, action, body);

    if (handlers.find(action) != handlers.end()) {
        handlers.find(action)->second->run(message, result);
    } else {
        *result = "ERROR\n";
    }
}

/**
 * Parses message that has to be handled.
 * 
 * First part will be action and everything after that body.
 * 
 * @author Lauri Orgla
 * 
 * @param input
 * @param action
 * @param body
 */
void Dispatcher::parseMessage(std::string input, std::string& action, std::string& body) {
    if (input.length() == 0)
        return;

    char *token;
    //bodyVec holds all body pieces after tokenizing, so body could be built later.
    std::vector<std::string> bodyVec;
    //Locale for converting action to uppercase
    std::locale locale;

    /** Convert input for strtok */
    char buffer[input.length()];
    strncpy(buffer, input.c_str(), input.length() + 1);
    token = strtok(buffer, " ");
    /* Conversion ends*/

    int number = 0;

    while (token != NULL) {
        //First part is action
        if (number == 0) {
            action = token;
        } else {
            //All other parts are pushed to vector
            bodyVec.push_back(token);
        }
        token = strtok(NULL, " ");
        number++;
    }

    if (action.length() == 0)
        action = input;

    for (std::vector<std::string>::iterator it = bodyVec.begin(); it != bodyVec.end(); ++it) {
        if (body.length() > 0) body.append(" ");
        body.append(it->data());
    }

    for (std::string::size_type i = 0; i < action.length(); ++i)
        action[i] = std::toupper(action[i], locale);
}
