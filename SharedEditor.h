#ifndef SHAREDEDITOR_H
#define SHAREDEDITOR_H

#include <vector>

#include "Message.h"
#include "NetworkServer.h"
#include "Symbol.h"

class SharedEditor {
private:
    NetworkServer& _server;
    int _siteId{};
    std::vector<Symbol> _symbols;
    int _counter=1;

    Symbol generateSymbol(char value, int index);
    void generateIndexBetween(Symbol &sym1, int pos1, Symbol &sym2, int pos2, std::vector<int> &newFractIndex);
    auto findInsertIndex(const Symbol &sym);
    auto findIndexByPos(const Symbol &sym);

public:
    SharedEditor() = delete;
    explicit SharedEditor(NetworkServer &server);
    int getSiteId();
    void localInsert(char value, int index);
    void localErase(int index);
    void process(const Message& m);
    void remoteInsert(Symbol sym);
    void remoteDelete(Symbol sym);
    std::string to_string();

};


#endif //SHAREDEDITOR_H
