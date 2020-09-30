#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <QChar>
#include <QTextCharFormat>
#include <stdexcept>

class Symbol {
private:
    QChar _value;
    QTextCharFormat _format;
    int _siteId;
    int _counter;
    std::vector<int> _fractIndex;
public:
    Symbol(QChar value, QTextCharFormat format, int siteId, int counter, std::vector<int> &fractIndex) :
        _value(value),
        _format(format),
        _siteId(siteId),
        _counter(counter),
        _fractIndex(fractIndex) {};

    int getFractIndexDigit(int pos) const;
    std::vector<int> getFractIndex() const;
    int getSiteId();
    size_t fractIndexSize();
    QChar getValue();
    QTextCharFormat getFormat();
};


#endif //SYMBOL_H
