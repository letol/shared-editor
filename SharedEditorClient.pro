QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    notepad.h \
    logindialog.h \
    onlineusersdialog.h \
    openfiledialog.h \
    registrationdialog.h \
    updateform.h \
    user.h

SOURCES         = \
    logindialog.cpp \
    main.cpp \
    notepad.cpp \
    onlineusersdialog.cpp \
    openfiledialog.cpp \
    registrationdialog.cpp \
    updateform.cpp \
    user.cpp

RESOURCES += \
    notepad.qrc

FORMS += \
    logindialog.ui \
    notepad.ui \
    onlineusersdialog.ui \
    openfiledialog.ui \
    registrationdialog.ui \
    updateform.ui

include(mock/mock.pri)
include(shared_editor/shared_editor.pri)

include(network/network.pri)
include(network/messages/messages.pri)

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target
