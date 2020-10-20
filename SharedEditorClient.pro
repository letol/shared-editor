QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    confirmpassword.h \
    notepad.h \
    logindialog.h \
    onlineusersdialog.h \
    openfiledialog.h \
    registrationdialog.h \
    updateformdialog.h \
    user.h

SOURCES         = \
    confirmpassword.cpp \
    logindialog.cpp \
    main.cpp \
    notepad.cpp \
    onlineusersdialog.cpp \
    openfiledialog.cpp \
    registrationdialog.cpp \
    updateformdialog.cpp \
    user.cpp

RESOURCES += \
    notepad.qrc

FORMS += \
    confirmpassword.ui \
    logindialog.ui \
    notepad.ui \
    onlineusersdialog.ui \
    openfiledialog.ui \
    registrationdialog.ui \
    updateformdialog.ui

include(mock/mock.pri)
include(shared_editor/shared_editor.pri)

include(network/network.pri)
include(network/messages/messages.pri)

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target
