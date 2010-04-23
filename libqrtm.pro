# -------------------------------------------------
# Project created by QtCreator 2010-04-08T00:36:49
# -------------------------------------------------
QT += network \
    webkit
TARGET = libqrtm
TEMPLATE = lib
DEFINES += RTMAPI_LIBRARY
SOURCES += src/loginview.cpp \
    src/request.cpp \
    src/rtmexception.cpp \
    src/rtmservice.cpp \
    src/libqjson/serializerrunnable.cpp \
    src/libqjson/serializer.cpp \
    src/libqjson/qobjecthelper.cpp \
    src/libqjson/parserrunnable.cpp \
    src/libqjson/parser.cpp \
    src/libqjson/json_scanner.cpp \
    src/libqjson/json_parser.cc \
    src/authentication.cpp \
    src/main.cpp \
    src/merih_deneme.cpp
HEADERS += src/libqrtm_global.h \
    src/loginview.h \
    src/request.h \
    src/rtm.h \
    src/rtmexception.h \
    src/rtmservice.h \
    src/libqjson/stack.hh \
    src/libqjson/serializerrunnable.h \
    src/libqjson/serializer.h \
    src/libqjson/qobjecthelper.h \
    src/libqjson/qjson_export.h \
    src/libqjson/qjson_debug.h \
    src/libqjson/position.hh \
    src/libqjson/parserrunnable.h \
    src/libqjson/parser_p.h \
    src/libqjson/parser.h \
    src/libqjson/location.hh \
    src/libqjson/json_scanner.h \
    src/libqjson/json_parser.hh \
    src/authentication.h
win32:DESTDIR = .\build\win32
unix:DESTDIR = ./build/unix
OTHER_FILES += src/libqjson/json_parser.yy
MOC_DIR = DESTDIR
OBJECTS_DIR = DESTDIR
