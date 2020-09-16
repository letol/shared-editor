QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    Message.h \
    NetworkServer.h \
    SharedEditor.h \
    Symbol.h \
    notepad.h
SOURCES         = \
                  Message.cpp \
                  NetworkServer.cpp \
                  SharedEditor.cpp \
                  Symbol.cpp \
                  main.cpp \
                  notepad.cpp

RESOURCES += notepad.qrc

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target

FORMS += \
    notepad.ui
