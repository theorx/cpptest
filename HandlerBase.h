/* 
 * File:   HandlerBase.h
 * Author: orx
 *
 * Created on August 24, 2014, 2:02 PM
 */

#ifndef HANDLERBASE_H
#define	HANDLERBASE_H

#include <iostream>
#include <string>
#include <stdio.h>

class HandlerBase {
public:
    HandlerBase();
    HandlerBase(const HandlerBase& orig);
    virtual ~HandlerBase();
    virtual void run(std::string message, std::string *result);
private:

};

#endif	/* HANDLERBASE_H */

