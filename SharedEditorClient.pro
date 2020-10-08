QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    notepad.h \

SOURCES         = \
    main.cpp \
    notepad.cpp \

RESOURCES += \
    notepad.qrc

FORMS += \
    notepad.ui

include(mock/mock.pri)
include(shared_editor/shared_editor.pri)

# install
target.path = /home/leonardo/Polito/2018-2019/Programmazione di Sistema/Malnati/
INSTALLS += target

