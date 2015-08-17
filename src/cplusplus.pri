





CONFIG+=c++14






CONFIG(debug,debug|release){
DEFINES *= _DEBUG
}else{
DEFINES *= NDEBUG
}






win32-msvc*{##xp support
QMAKE_CXXFLAGS += /D "_USING_V110_SDK71_"
QMAKE_LFLAGS += /SUBSYSTEM:CONSOLE",5.01"
QMAKE_LFLAGS += /SAFESEH:NO
}




win32-msvc*{
QMAKE_CXXFLAGS += /bigobj
}





linux-g++ {
LIBS+=-lpthread
}





*g++{
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
}










