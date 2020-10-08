QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    notepad.h \
    logindialog.h \
    registrationdialog.h \
    user.h

SOURCES         = \
    logindialog.cpp \
    main.cpp \
    notepad.cpp \
    registrationdialog.cpp \
    user.cpp

RESOURCES += \
    notepad.qrc

FORMS += \
    logindialog.ui \
    notepad.ui \
    registrationdialog.ui

include(mock/mock.pri)
include(shared_editor/shared_editor.pri)

include(network/network.pri)
include(network/messages/messages.pri)

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target
