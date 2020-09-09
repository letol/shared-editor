QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = SharedEditorClient

HEADERS         = \
    Message.h \
    NetworkServer.h \
    SharedEditor.h \
    SharedEditorClient.h \
    Symbol.h
SOURCES         = \
                  Message.cpp \
                  NetworkServer.cpp \
                  SharedEditor.cpp \
                  SharedEditorClient.cpp \
                  Symbol.cpp \
                  main.cpp

RESOURCES += textedit.qrc
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

EXAMPLE_FILES = textedit.qdoc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/textedit
INSTALLS += target
