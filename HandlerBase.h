#ifndef HANDLERBASE_H
#define	HANDLERBASE_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "Message.h"

class Session;

class HandlerBase {
public:
    HandlerBase();
    HandlerBase(const HandlerBase& orig);
    virtual ~HandlerBase();
    virtual void run(Message *msg);
private:

};

#endif	/* HANDLERBASE_H */

