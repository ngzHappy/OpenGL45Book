include($$PWD/../configure.pri.user)
include($$PWD/../cplusplus.pri)


TEMPLATE = lib
CONFIG += qt warn_on
QT -= gui

# The ABI version.

!win32:VERSION = 1.0.0

# 1.0.0 is the first stable ABI.
# The next binary incompatible change will be 2.0.0 and so on.
# The existing QuaZIP policy on changing ABI requires to bump the
# major version of QuaZIP itself as well. Note that there may be
# other reasons for chaging the major version of QuaZIP, so
# in case where there is a QuaZIP major version bump but no ABI change,
# the VERSION variable will stay the same.

# For example:

# QuaZIP 1.0 is released after some 0.x, keeping binary compatibility.
# VERSION stays 1.0.0.
# Then some binary incompatible change is introduced. QuaZIP goes up to
# 2.0, VERSION to 2.0.0.
# And so on.
CONFIG +=  staticlib
DEFINES *= QUAZIP_STATIC

# This one handles dllimport/dllexport directives.
#DEFINES += QUAZIP_BUILD

# Input
include(quazip.pri)

TARGET = QLQUAZIP


CONFIG(debug,debug|release){
DESTDIR = $$OUT__DIR__BASE__/bind
}else{
DESTDIR = $$OUT__DIR__BASE__/bin
}



