//
// Created by leonardo on 07/05/19.
//

#include "sharededitor.h"

SharedEditor::SharedEditor(NetworkServer &server) : _server(server) {
    this->_siteId = _server.connect(this);
    Symbol newSym = generateSymbol(QChar::ParagraphSeparator, QTextCharFormat(), QTextBlockFormat(), 0);
    auto it = _symbols.begin();
    _symbols.insert(it, newSym);
}

int SharedEditor::getSiteId() {
    return _siteId;
}

int SharedEditor::getSymbolSiteId(int index) {
    auto it = _symbols.begin();
    it+=index;
    return it->getSiteId();
}

QTextCharFormat SharedEditor::getSymbolFormat(int index) {
    auto it = _symbols.begin();
    it+=index;
    return it->getCharFormat();
}

void SharedEditor::localInsert(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index) {
    Symbol newSym = generateSymbol(value, charFormat, blockFormat, index);
    auto it = _symbols.begin();
    it+=index;
    _symbols.insert(it, newSym);
    EditingMessage msg(newSym, MSG_INSERT, this->_siteId);
    _server.send(msg);
}

Symbol SharedEditor::generateSymbol(QChar value, QTextCharFormat charFormat, QTextBlockFormat blockFormat, int index) {
    QVector<int> newFractIndex;
    if (index == 0) {
        if (_symbols.empty()) {
            newFractIndex.push_back(1);
        } else {
            Symbol sym2 = _symbols[index];
            QVector<int> startFractIndex;
            int size = sym2.fractIndexSize();
            for (int i = 0; i < size - 1; ++i) {
                startFractIndex.push_back(0);
            }
            Symbol sym1('$', QTextCharFormat(), QTextBlockFormat(), this->_siteId, 0, startFractIndex);
            generateIndexBetween(sym1, 0, sym2, 0, newFractIndex);
        }
    } else if (_symbols.size() == index) {
        Symbol sym = _symbols[index - 1];
        newFractIndex.push_back(sym.getFractIndexDigit(0) + 1);
    } else {
        Symbol sym2 = _symbols[index];
        Symbol sym1 = _symbols[index - 1];
        generateIndexBetween(sym1, 0, sym2, 0, newFractIndex);
    }

    return Symbol(value, charFormat, blockFormat, this->_siteId, this->_counter++, newFractIndex);
}

void
SharedEditor::generateIndexBetween(Symbol &sym1, int pos1, Symbol &sym2, int pos2, QVector<int> &newFractIndex) {
    int digit1 = sym1.getFractIndexDigit(pos1);
    int digit2 = sym2.getFractIndexDigit(pos2);

    if (digit1 == -1 && digit2 == -1) {
        // [ x , ... , y ]       [ x , ... , z ]       =>   [ x , ... , y , 1 ]
        newFractIndex.push_back(1);

    } else if (digit1 == -1) {
        // [ x , ... , y ]       [ x , ... , y , z ]   =>   [ x , ... , y , 0 , 1 ]
        newFractIndex.push_back(0);
        newFractIndex.push_back(1);

    } else if (digit2 == -1) {
        // [ x , ... , y , 2 ]   [ x , ... , y ]       =>   [ x , ... , y , 3 ]
        newFractIndex.push_back(digit1+1);

    } else if (digit2 - digit1 > 1) {
        // [ x , ... , y , 1 ]   [ x , ... , y , 4 ]   =>   [ x , ... , y , 2 ]
        newFractIndex.push_back(digit1+1);

    } else if (digit2 - digit1 == 1) {
        // [ x , ... , y , 3 ]   [ x , ... , y , 4 ]   =>   [ x , ... , y , 3 , ? ] + recursion
        newFractIndex.push_back(digit1);
        generateIndexBetween(sym1, pos1+1, sym2, pos2+1, newFractIndex);

    } else if (digit2 - digit1 == 0) {
        // [ x , ... , y , 2 ]   [ x , ... , y , 2 ]   =>   [ x , ... , y , 2 ] + recursion
        newFractIndex.push_back(digit1);
        generateIndexBetween(sym1, pos1+1, sym2, pos2+1, newFractIndex);
    }
}

void SharedEditor::localErase(int index) {
    EditingMessage msg(_symbols[index], MSG_ERASE, this->_siteId);
    auto it = _symbols.begin();
    it+=index;
    _symbols.erase(it);
    _server.send(msg);
}

/*
auto SharedEditor::findInsertIndex(const Symbol &sym) {
    auto it = _symbols.begin();
    auto newIndex = it;
    bool flag = true;
    do {
        bool innerFlag = true;
        int pos=0;
        do {
            int currentDigit = it->getFractIndexDigit(pos);
            int newDigit = sym.getFractIndexDigit(pos);

            if (currentDigit == -1) {
                newIndex = ++it;
                innerFlag = false;

            } else if (newDigit == -1) {
                // impossibile

            } else if (currentDigit == newDigit) {
                pos++;

            } else if (currentDigit < newDigit) {
                newIndex = ++it;
                innerFlag = false;

            } else if (currentDigit > newDigit) {
                innerFlag = false;
                flag = false;
            }
        } while (innerFlag);
    } while (flag);
    return newIndex;
}
 */

auto SharedEditor::findInsertIndex(const Symbol &sym) {
    auto it = _symbols.begin();

    while (it != _symbols.end() && it->getFractIndex() < sym.getFractIndex()){
        it++;
    }

    return it;
}

auto SharedEditor::findIndexByPos(const Symbol &sym) {
    auto it = _symbols.begin();

    while (it != _symbols.end() && it->getFractIndex() != sym.getFractIndex()) {
        it++;
    }

    return it;
}


QString SharedEditor::to_string() {
    QString str;
    for (auto it = _symbols.begin(); it != _symbols.end(); it++) {
        str.push_back(it->getValue());
    }
    return str;
}

void SharedEditor::remoteInsert(Symbol sym) {
    auto index = findInsertIndex(sym);
    remoteCharInserted(sym.getSiteId(), sym.getValue(), sym.getCharFormat(), sym.getBlockFormat(), index - _symbols.begin());
    _symbols.insert(index, sym);
}

void SharedEditor::remoteDelete(Symbol sym) {
    auto index = findIndexByPos(sym);
    remoteCharDeleted(sym.getSiteId(), index - _symbols.begin());
    _symbols.erase(index);
}

void SharedEditor::process(const EditingMessage &m) {
    if (m.getOperation() == MSG_INSERT) {
        remoteInsert(m.getSymbol());
    } else if (m.getOperation() == MSG_ERASE) {
        remoteDelete(m.getSymbol());
    }
}

int SharedEditor::symbolCount() {
    return _symbols.size();
}
