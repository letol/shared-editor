QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    controller.h \
    notepad.h \
    user.h

SOURCES         = \
    controller.cpp \
    main.cpp \
    notepad.cpp \
    user.cpp

RESOURCES += \
    notepad.qrc

FORMS += \
    notepad.ui

include(shared_editor/shared_editor.pri)
include(network/network.pri)
include(network/messages/messages.pri)
include(dialogs/dialogs.pri)

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target
