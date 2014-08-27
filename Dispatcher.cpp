#include "Dispatcher.h"

/**
 * @author Lauri Orgla
 */
Dispatcher::Dispatcher() {
}

/**
 * @author Lauri Orgla
 * @param orig
 */
Dispatcher::Dispatcher(const Dispatcher& orig) {
}

/**
 * @author Lauri Orgla
 */
Dispatcher::~Dispatcher() {
    /**
     * Deletes all
     */
    for (std::map<std::string, HandlerBase * >::iterator it = this->handlers.begin(); it != this->handlers.end(); ++it) {
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
        std::cout << "[System] Registrering handler: " << name << " ... done!" << std::endl;
        handlers.insert(std::pair<std::string, HandlerBase*>(name, handler));
    } else {
        //deletes handler in case if handler is not added to map
        //Garbage collection.
        delete handler;
        std::cout << "[System] Handler with name " << name << " Is already registered." << std::endl;
    }
}

/**
 * @author Lauri Orgla
 * 
 * @param message
 * @param result
 * @param self
 * @param session_pool
 */
void Dispatcher::handle(Message *msg) {
    //Remove newline characters
    for (int i = 0; i < msg->message.length(); i++) {
        if (msg->message[i] == '\n') {
            msg->message[i] = ' ';
        }
    }
    std::string body;
    std::string action;
    parseMessage(msg->message, action, body);
    msg->message = body;
    if (handlers.find(action) != handlers.end()) {
        handlers.find(action)->second->run(msg);
    } else {
        *msg->result = "ERROR\n";
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
