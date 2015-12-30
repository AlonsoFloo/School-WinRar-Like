TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    filepool.cpp \
    zipper.cpp \
    zippedbuffer.cpp \
    zippedbufferpool.cpp \
    winuscompressor.cpp \
    writer.cpp \
    reader.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    filepool.h \
    zipper.h \
    zippedbuffer.h \
    zippedbufferpool.h \
    winuscompressor.h \
    writer.h \
    reader.h
