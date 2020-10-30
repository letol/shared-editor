#ifndef SHAREDEDITOR_H
#define SHAREDEDITOR_H

#include <QVector>
#include <QObject>
#include <QChar>
#include <QString>
#include <QUuid>

#include "editingmessage.h"
#include "symbol.h"

class SharedEditor : public QObject
{
    Q_OBJECT

public:
    SharedEditor() = delete;
    SharedEditor(QUuid siteId);
    QUuid getSiteId();
    QString getUserEmail();
    void setUserEmail(QString userEmail);
    QVector<Symbol>& getSymbols();
    QUuid getSymbolSiteId(int index);
    QString getSymbolOwner(int index);
    QTextCharFormat getSymbolFormat(int index);
    void localInsert(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void localErase(int index);
    void remoteInsert(Symbol sym);
    void remoteDelete(Symbol sym);
    QString to_string();
    int symbolCount();
    void reset();

public slots:
    void process(const EditingMessage& m);

signals:
    void localChange(const EditingMessage& m);
    void remoteCharInserted(QUuid remoteSiteId, QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void remoteCharDeleted(QUuid remoteSiteId, int index);

private:
    QUuid _siteId{};
    QString _userEmail;
    QVector<Symbol> _symbols;
    int _counter=1;

    Symbol generateSymbol(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index);
    void generateIndexBetween(Symbol &sym1, int pos1, Symbol &sym2, int pos2, QVector<int> &newFractIndex);
    auto findInsertIndex(const Symbol &sym);
    auto findIndexByPos(const Symbol &sym);
};


#endif //SHAREDEDITOR_H
