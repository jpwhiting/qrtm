# -------------------------------------------------
# Project created by QtCreator 2010-04-08T00:36:49
# -------------------------------------------------
QT += network
TARGET = qrtm
TEMPLATE = lib
DEFINES += RTMAPI_LIBRARY
CONFIG += link_pkgconfig create_pc create_prl no_install_prl
PKGCONFIG += QJson

SOURCES += src/request.cpp \
    src/authentication.cpp \
    src/service.cpp
HEADERS += src/libqrtm_global.h \
    src/request.h \
    src/rtm.h \
    src/authentication.h \
    src/service.h
OTHER_FILES += qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

win32 { 
    DESTDIR = .\build\win32
    MOC_DIR = .\build\objects
    OBJECTS_DIR = .\build\objects
}
unix { 
target.path = /usr/local/lib

QMAKE_PKGCONFIG_NAME = qrtm
QMAKE_PKGCONFIG_DESCRIPTION = Qt Remember The Milk library
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$target.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig

headers.path = /usr/local/include/qrtm
headers.files = src/libqrtm_global.h \
    src/loginview.h \
    src/request.h \
    src/rtm.h \
    src/authentication.h \
    src/service.h

}

INSTALLS += target headers
