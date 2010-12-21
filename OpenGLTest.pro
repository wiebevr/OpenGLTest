TARGET = OpenGLTest

OBJECTS_DIR = ./build
MOC_DIR = ./build
RCC_DIR = ./build

QT += opengl

HEADERS += widget.h \

SOURCES += widget.cpp \
           main.cpp
#QMAKESPEC = /home/plomplot/School/EmbeddedOS/oe_igep/openembedded/recipes/my-projects

target.path = /usr/bin
INSTALLS += target
