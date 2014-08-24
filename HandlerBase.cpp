/* 
 * File:   HandlerBase.cpp
 * Author: orx
 * 
 * Created on August 24, 2014, 2:02 PM
 */

#include "HandlerBase.h"

HandlerBase::HandlerBase() {
}

HandlerBase::HandlerBase(const HandlerBase& orig) {
}

HandlerBase::~HandlerBase() {
}

void HandlerBase::run(std::string message, std::string *result) {
    std::cout << "Running handler.." << message << std::endl;
    *result = "GET sample result yo nigger.. or something\n";
}
