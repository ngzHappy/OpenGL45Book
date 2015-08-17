include($$PWD/../../configure.pri.user)
include($$PWD/../../cplusplus.pri)

QT += core
TARGET = QLAssimp
TEMPLATE = lib

DEFINES*=ASSIMP_BUILD_DLL_EXPORT
##ASSIMP_DLL

INCLUDEPATH+=$$PWD/..


include($$PWD/../assimp.pri)



CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
}else{
DESTDIR = $$OUT__DIR__BASE__/bin
}

