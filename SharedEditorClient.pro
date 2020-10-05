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
    logindialog.h \
    notepad.h \
    registrationdialog.h \
    user.h
SOURCES         = \
                  Message.cpp \
                  NetworkServer.cpp \
                  SharedEditor.cpp \
                  Symbol.cpp \
                  logindialog.cpp \
                  main.cpp \
                  notepad.cpp \
                  registrationdialog.cpp \
                  user.cpp

RESOURCES += notepad.qrc

include(network/network.pri)
include(network/messages/messages.pri)

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target

FORMS += \
    logindialog.ui \
    notepad.ui \
    registrationdialog.ui
