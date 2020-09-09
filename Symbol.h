#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>
#include <stdexcept>

class Symbol {
private:
    char _value;
    int _siteId;
    int _counter;
    std::vector<int> _fractIndex;
public:
    Symbol(char value, int siteId, int counter, std::vector<int> &fractIndex);
    int getFractIndexDigit(int pos) const;
    std::vector<int> getFractIndex() const;
    int getSiteId();
    size_t fractIndexSize();
    char getValue();
};


#endif //SYMBOL_H
