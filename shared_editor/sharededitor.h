#ifndef SHAREDEDITOR_H
#define SHAREDEDITOR_H

#include <QObject>
#include <vector>
#include <QChar>
#include <QString>

#include "editingmessage.h"
#include "networkserver.h"
#include "symbol.h"

class SharedEditor : public QObject
{
    Q_OBJECT

public:
    SharedEditor() = delete;
    explicit SharedEditor(NetworkServer &server);
    int getSiteId();
    int getSymbolSiteId(int index);
    QTextCharFormat getSymbolFormat(int index);
    void localInsert(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void localErase(int index);
    void process(const EditingMessage& m);
    void remoteInsert(Symbol sym);
    void remoteDelete(Symbol sym);
    QString to_string();
    int symbolCount();

signals:
    void remoteCharInserted(int remoteSiteId, QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void remoteCharDeleted(int remoteSiteId, int index);

private:
    NetworkServer& _server;
    int _siteId{};
    std::vector<Symbol> _symbols;
    int _counter=1;

    Symbol generateSymbol(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void generateIndexBetween(Symbol &sym1, int pos1, Symbol &sym2, int pos2, std::vector<int> &newFractIndex);
    auto findInsertIndex(const Symbol &sym);
    auto findIndexByPos(const Symbol &sym);
};


#endif //SHAREDEDITOR_H
