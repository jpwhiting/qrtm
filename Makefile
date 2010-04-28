#############################################################################
# Makefile for building: liblibqrtm.so.1.0.0
# Generated by qmake (2.01a) (Qt 4.6.2) on: �ar Nis 28 21:20:59 2010
# Project:  libqrtm.pro
# Template: lib
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile libqrtm.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DRTMAPI_LIBRARY -DQT_WEBKIT_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtWebKit -I/usr/include/qt4 -Ibuild/objects
LINK          = g++
LFLAGS        = -shared -Wl,-soname,liblibqrtm.so.1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtWebKit -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/objects/

####### Files

SOURCES       = src/loginview.cpp \
		src/request.cpp \
		src/libqjson/serializerrunnable.cpp \
		src/libqjson/serializer.cpp \
		src/libqjson/qobjecthelper.cpp \
		src/libqjson/parserrunnable.cpp \
		src/libqjson/parser.cpp \
		src/libqjson/json_scanner.cpp \
		src/libqjson/json_parser.cc \
		src/authentication.cpp \
		src/main.cpp \
		src/service.cpp build/objects/moc_loginview.cpp \
		build/objects/moc_request.cpp \
		build/objects/moc_serializerrunnable.cpp \
		build/objects/moc_parserrunnable.cpp \
		build/objects/moc_authentication.cpp \
		build/objects/moc_service.cpp
OBJECTS       = build/objects/loginview.o \
		build/objects/request.o \
		build/objects/serializerrunnable.o \
		build/objects/serializer.o \
		build/objects/qobjecthelper.o \
		build/objects/parserrunnable.o \
		build/objects/parser.o \
		build/objects/json_scanner.o \
		build/objects/json_parser.o \
		build/objects/authentication.o \
		build/objects/main.o \
		build/objects/service.o \
		build/objects/moc_loginview.o \
		build/objects/moc_request.o \
		build/objects/moc_serializerrunnable.o \
		build/objects/moc_parserrunnable.o \
		build/objects/moc_authentication.o \
		build/objects/moc_service.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		libqrtm.pro
QMAKE_TARGET  = libqrtm
DESTDIR       = build/unix/
TARGET        = liblibqrtm.so.1.0.0
TARGETA       = build/unix/liblibqrtm.a
TARGETD       = liblibqrtm.so.1.0.0
TARGET0       = liblibqrtm.so
TARGET1       = liblibqrtm.so.1
TARGET2       = liblibqrtm.so.1.0

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  build/unix/$(TARGET)

build/unix/$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) build/unix/ || $(MKDIR) build/unix/ 
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)
	-$(DEL_FILE) build/unix/$(TARGET)
	-$(DEL_FILE) build/unix/$(TARGET0)
	-$(DEL_FILE) build/unix/$(TARGET1)
	-$(DEL_FILE) build/unix/$(TARGET2)
	-$(MOVE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2) build/unix/



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

Makefile: libqrtm.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtWebKit.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile libqrtm.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtWebKit.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile libqrtm.pro

dist: 
	@$(CHK_DIR_EXISTS) build/objects/libqrtm1.0.0 || $(MKDIR) build/objects/libqrtm1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/objects/libqrtm1.0.0/ && $(COPY_FILE) --parents src/libqrtm_global.h src/loginview.h src/request.h src/rtm.h src/libqjson/stack.hh src/libqjson/serializerrunnable.h src/libqjson/serializer.h src/libqjson/qobjecthelper.h src/libqjson/qjson_export.h src/libqjson/qjson_debug.h src/libqjson/position.hh src/libqjson/parserrunnable.h src/libqjson/parser_p.h src/libqjson/parser.h src/libqjson/location.hh src/libqjson/json_scanner.h src/libqjson/json_parser.hh src/authentication.h src/service.h build/objects/libqrtm1.0.0/ && $(COPY_FILE) --parents src/loginview.cpp src/request.cpp src/libqjson/serializerrunnable.cpp src/libqjson/serializer.cpp src/libqjson/qobjecthelper.cpp src/libqjson/parserrunnable.cpp src/libqjson/parser.cpp src/libqjson/json_scanner.cpp src/libqjson/json_parser.cc src/authentication.cpp src/main.cpp src/service.cpp build/objects/libqrtm1.0.0/ && (cd `dirname build/objects/libqrtm1.0.0` && $(TAR) libqrtm1.0.0.tar libqrtm1.0.0 && $(COMPRESS) libqrtm1.0.0.tar) && $(MOVE) `dirname build/objects/libqrtm1.0.0`/libqrtm1.0.0.tar.gz . && $(DEL_FILE) -r build/objects/libqrtm1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) build/unix/$(TARGET) 
	-$(DEL_FILE) build/unix/$(TARGET0) build/unix/$(TARGET1) build/unix/$(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: build/objects/moc_loginview.cpp build/objects/moc_request.cpp build/objects/moc_serializerrunnable.cpp build/objects/moc_parserrunnable.cpp build/objects/moc_authentication.cpp build/objects/moc_service.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) build/objects/moc_loginview.cpp build/objects/moc_request.cpp build/objects/moc_serializerrunnable.cpp build/objects/moc_parserrunnable.cpp build/objects/moc_authentication.cpp build/objects/moc_service.cpp
build/objects/moc_loginview.cpp: src/loginview.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/loginview.h -o build/objects/moc_loginview.cpp

build/objects/moc_request.cpp: src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/request.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/request.h -o build/objects/moc_request.cpp

build/objects/moc_serializerrunnable.cpp: src/libqjson/qjson_export.h \
		src/libqjson/serializerrunnable.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/libqjson/serializerrunnable.h -o build/objects/moc_serializerrunnable.cpp

build/objects/moc_parserrunnable.cpp: src/libqjson/qjson_export.h \
		src/libqjson/parserrunnable.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/libqjson/parserrunnable.h -o build/objects/moc_parserrunnable.cpp

build/objects/moc_authentication.cpp: src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/request.h \
		src/authentication.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/authentication.h -o build/objects/moc_authentication.cpp

build/objects/moc_service.cpp: src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/authentication.h \
		src/request.h \
		src/service.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/service.h -o build/objects/moc_service.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

build/objects/loginview.o: src/loginview.cpp src/loginview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/loginview.o src/loginview.cpp

build/objects/request.o: src/request.cpp src/request.h \
		src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/request.o src/request.cpp

build/objects/serializerrunnable.o: src/libqjson/serializerrunnable.cpp src/libqjson/serializerrunnable.h \
		src/libqjson/qjson_export.h \
		src/libqjson/parserrunnable.h \
		src/libqjson/serializer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/serializerrunnable.o src/libqjson/serializerrunnable.cpp

build/objects/serializer.o: src/libqjson/serializer.cpp src/libqjson/serializer.h \
		src/libqjson/qjson_export.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/serializer.o src/libqjson/serializer.cpp

build/objects/qobjecthelper.o: src/libqjson/qobjecthelper.cpp src/libqjson/qobjecthelper.h \
		src/libqjson/qjson_export.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/qobjecthelper.o src/libqjson/qobjecthelper.cpp

build/objects/parserrunnable.o: src/libqjson/parserrunnable.cpp src/libqjson/parserrunnable.h \
		src/libqjson/qjson_export.h \
		src/libqjson/parser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/parserrunnable.o src/libqjson/parserrunnable.cpp

build/objects/parser.o: src/libqjson/parser.cpp src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/libqjson/parser_p.h \
		src/libqjson/json_parser.hh \
		src/libqjson/stack.hh \
		src/libqjson/json_scanner.h \
		src/libqjson/qjson_debug.h \
		src/libqjson/location.hh \
		src/libqjson/position.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/parser.o src/libqjson/parser.cpp

build/objects/json_scanner.o: src/libqjson/json_scanner.cpp src/libqjson/qjson_debug.h \
		src/libqjson/json_scanner.h \
		src/libqjson/parser_p.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/libqjson/json_parser.hh \
		src/libqjson/stack.hh \
		src/libqjson/location.hh \
		src/libqjson/position.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/json_scanner.o src/libqjson/json_scanner.cpp

build/objects/json_parser.o: src/libqjson/json_parser.cc src/libqjson/json_parser.hh \
		src/libqjson/stack.hh \
		src/libqjson/parser_p.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/libqjson/json_scanner.h \
		src/libqjson/qjson_debug.h \
		src/libqjson/location.hh \
		src/libqjson/position.hh
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/json_parser.o src/libqjson/json_parser.cc

build/objects/authentication.o: src/authentication.cpp src/authentication.h \
		src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/request.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/authentication.o src/authentication.cpp

build/objects/main.o: src/main.cpp src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/authentication.h \
		src/request.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/main.o src/main.cpp

build/objects/service.o: src/service.cpp src/service.h \
		src/rtm.h \
		src/libqrtm_global.h \
		src/libqjson/parser.h \
		src/libqjson/qjson_export.h \
		src/authentication.h \
		src/request.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/service.o src/service.cpp

build/objects/moc_loginview.o: build/objects/moc_loginview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/moc_loginview.o build/objects/moc_loginview.cpp

build/objects/moc_request.o: build/objects/moc_request.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/moc_request.o build/objects/moc_request.cpp

build/objects/moc_serializerrunnable.o: build/objects/moc_serializerrunnable.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/moc_serializerrunnable.o build/objects/moc_serializerrunnable.cpp

build/objects/moc_parserrunnable.o: build/objects/moc_parserrunnable.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/moc_parserrunnable.o build/objects/moc_parserrunnable.cpp

build/objects/moc_authentication.o: build/objects/moc_authentication.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/moc_authentication.o build/objects/moc_authentication.cpp

build/objects/moc_service.o: build/objects/moc_service.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/objects/moc_service.o build/objects/moc_service.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

