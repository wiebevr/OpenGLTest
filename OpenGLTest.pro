TARGET = OpenGLTest

OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

QT += opengl

HEADERS += widget.h \

SOURCES += widget.cpp \
           main.cpp
QMAKESPEC = ..

target.path = /usr/bin
INSTALLS += target
