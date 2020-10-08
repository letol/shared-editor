#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <QChar>
#include <QTextCharFormat>
#include <stdexcept>

class Symbol {
private:
    QChar _value;
    QTextCharFormat _charFormat;
    QTextBlockFormat _blockFormat;
    int _siteId;
    int _counter;
    std::vector<int> _fractIndex;
public:
    Symbol(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int siteId, int counter, std::vector<int> &fractIndex) :
        _value(value),
        _charFormat(charFormat),
        _blockFormat(blockFormat),
        _siteId(siteId),
        _counter(counter),
        _fractIndex(fractIndex) {};

    int getFractIndexDigit(int pos) const;
    std::vector<int> getFractIndex() const;
    int getSiteId();
    size_t fractIndexSize();
    QChar getValue();
    QTextCharFormat getCharFormat();
    QTextBlockFormat getBlockFormat();
};


#endif //SYMBOL_H
