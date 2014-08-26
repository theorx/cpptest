#ifndef HANDLERBASE_H
#define	HANDLERBASE_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

class Session;

class HandlerBase {
public:
    HandlerBase();
    HandlerBase(const HandlerBase& orig);
    virtual ~HandlerBase();
    virtual void run(std::string message, std::string *result, Session* self, std::vector<Session*> *session_pool);
private:

};

#endif	/* HANDLERBASE_H */

