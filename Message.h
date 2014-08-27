/* 
 * File:   Message.h
 * Author: root
 *
 * Created on August 27, 2014, 11:11 PM
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#include "Session.h"
#include <vector>
class Session;

struct Message {
    std::string message;
    std::string *result;
    Session* self;
    std::vector<Session*> *session_pool;
};

#endif	/* MESSAGE_H */

