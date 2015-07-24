#-------------------------------------------------
#
# Project created by QtCreator 2012-04-10T14:20:02
#
#-------------------------------------------------

QT       += core opengl widgets

#
# install QGLWidget libqglviewer-dev
#
#

TARGET = desktop
TEMPLATE = app

linux-g++ {
    PLATFORM = x86
    QMAKE_CFLAGS += -pg
    QMAKE_CXXFLAGS += -pg
    QMAKE_LFLAGS += -pg
}

linux-mips-g++:PLATFORM = mips
linux-arm-g++:PLATFORM = arm

win32-g++ {
    PLATFORM = win32
    DESTDIR = ../Desktop_win32
}

message("$$PLATFORM")

MOC_DIR = .$${PLATFORM}_moc
OBJECTS_DIR = .$${PLATFORM}_obj



SOURCES += main.cpp\
    desktop.cpp \
    globalkeyboardevent.cpp \
    setapp.cpp \
    sysenv.cpp \
    icon.cpp \
    dcomponent.cpp \
    panel.cpp

HEADERS  += \
    common.h \
    desktop.h \
    globalkeyboardevent.h \
    setapp.h \
    sysenv.h \
    icon.h \
    dcomponent.h \
    panel.h

FORMS    +=

OTHER_FILES += \
    README.txt

RESOURCES += \
    aosres.qrc
