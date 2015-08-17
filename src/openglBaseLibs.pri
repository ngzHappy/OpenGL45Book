



DEFINES *= GLEW_NO_GLU
DEFINES *= GLEW_STATIC
DEFINES *= QUAZIP_STATIC
DEFINES *= ASSIMP_DLL




#you need change here in different platform
#glxinfo |grep "OpenGL version"
#

win32:{
Local_Codec = GBK
}else{
Local_Codec = UTF-8
}

DEFINES += LOCAL_CODEC_NAME=$$join(Local_Codec,,"\\\"","\\\"")


win32:{
LIBS+= -lopengl32 -lgdi32 -luser32 -lkernel32
}


linux:{
###libglu1-mesa-dev
###libgl1-mesa-dev
LIBS+=-lXmu -lXi -lGL -lXext -lX11
}















