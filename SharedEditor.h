#ifndef SHAREDEDITOR_H
#define SHAREDEDITOR_H

#include <QObject>
#include <vector>
#include <QChar>
#include <QString>

#include "Message.h"
#include "NetworkServer.h"
#include "Symbol.h"

class SharedEditor : public QObject
{
    Q_OBJECT

public:
    SharedEditor() = delete;
    explicit SharedEditor(NetworkServer &server);
    int getSiteId();
    int getSymbolSiteId(int index);
    void localInsert(QChar value, int index);
    void localErase(int index);
    void process(const Message& m);
    void remoteInsert(Symbol sym);
    void remoteDelete(Symbol sym);
    QString to_string();

signals:
    void remoteCharInserted(int remoteSiteId, QChar value, int index);
    void remoteCharDeleted(int remoteSiteId, int index);

private:
    NetworkServer& _server;
    int _siteId{};
    std::vector<Symbol> _symbols;
    int _counter=1;

    Symbol generateSymbol(QChar value, int index);
    void generateIndexBetween(Symbol &sym1, int pos1, Symbol &sym2, int pos2, std::vector<int> &newFractIndex);
    auto findInsertIndex(const Symbol &sym);
    auto findIndexByPos(const Symbol &sym);
};


#endif //SHAREDEDITOR_H
