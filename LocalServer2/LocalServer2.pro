
QT       += core gui widgets network

TARGET = LocalServer2
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    localserver.cpp \
    thread.cpp \
    splay.cpp \
    arbolsplay.cpp

HEADERS += \
        widget.h \
    localserver.h \
    thread.h \
    nodo.h \
    arbolsplay.h

FORMS += \
        widget.ui
QMAKE_CXXFLAGS += -std=gnu++11
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
