#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

#include "Message.h"

class SharedEditor;

class NetworkServer {
private:
    std::vector<SharedEditor*> _connectedEditors;
    std::queue<Message> _msgQ;
    int _counter = 0;
public:
    ~NetworkServer();
    int connect(SharedEditor *sharedEditor);
    void disconnect(SharedEditor *sharedEditor);
    void send(const Message& m);
    void dispatchMessages();
};


#endif //NETWORKSERVER_H
