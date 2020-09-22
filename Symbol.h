#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <QChar>
#include <stdexcept>

class Symbol {
private:
    QChar _value;
    int _siteId;
    int _counter;
    std::vector<int> _fractIndex;
public:
    Symbol(QChar value, int siteId, int counter, std::vector<int> &fractIndex) :
        _value(value),
        _siteId(siteId),
        _counter(counter),
        _fractIndex(fractIndex) {};

    int getFractIndexDigit(int pos) const;
    std::vector<int> getFractIndex() const;
    int getSiteId();
    size_t fractIndexSize();
    QChar getValue();
};


#endif //SYMBOL_H
