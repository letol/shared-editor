//
// Created by leonardo on 07/05/19.
//

#include "networkserver.h"
#include "sharededitor.h"

int NetworkServer::connect(SharedEditor *sharedEditor) {
    _connectedEditors.insert(_connectedEditors.end(), sharedEditor);
    return _counter++;
}

void NetworkServer::disconnect(SharedEditor *sharedEditor) {
    auto iterator = std::find(_connectedEditors.cbegin(), _connectedEditors.cend(), sharedEditor);
    if (iterator != _connectedEditors.cend()) {
        _connectedEditors.erase(iterator);
    }
}

void NetworkServer::send(const EditingMessage &m) {
    _msgQ.push(m);
}

void NetworkServer::dispatchMessages() {
    while (!_msgQ.empty()) {
        EditingMessage m = _msgQ.front();
        std::for_each(_connectedEditors.cbegin(), _connectedEditors.cend(),[&m](SharedEditor *sharedEditor){
            if (sharedEditor->getSiteId() != m.getSenderSiteId()) {
                sharedEditor->process(m);
            }
        });
        _msgQ.pop();
    }
}

NetworkServer::~NetworkServer() {
    std::for_each(_connectedEditors.cbegin(), _connectedEditors.cend(), [this](SharedEditor *sharedEditor){disconnect(sharedEditor);});
}
