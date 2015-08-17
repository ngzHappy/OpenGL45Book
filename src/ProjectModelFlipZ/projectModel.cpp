
#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QString>
#include <string>
#include <QList>
#include <OpenGLTool/ModelLoader.hpp>
#include <OpenGLTool/ModelLoaderCallbacks.hpp>
#include <QFileInfo>
namespace  {
enum Type :unsigned int {
    Texture = 1,
    Normal = 2,
    Vertex = 4 ,
    None = 0
};

struct Command{
    std::string objectFileName ;
    std::string projectObjectFileName ;
    unsigned int type = Type::None ;

};

template<typename T>
class FlipZCallBack : public T{
public:
   virtual void findPoint(int a0, float a1, float a2, float a3)   override{
        T::findPoint(a0,a1,a2,-a3);
    }
};

void eval_command(const Command & command_){
	QFileInfo info(QString::fromLocal8Bit(command_.objectFileName.data()));
 
    gl::ModelLoaderCallBack * callBack = 0;
    switch (command_.type) {
    case Vertex:{
        callBack = new FlipZCallBack<gl::VertexElementCallBack>;
    }
        break;
    case Vertex|Normal:{
        callBack = new FlipZCallBack<gl::VertexNormalElementCallBack>;
    }
        break;
    case Vertex|Normal|Texture:{
        callBack = \
                new FlipZCallBack<gl::VertexTextureNormalElementCallBack>;
    }
        break;
    default:
        break;
    }
    if(0==callBack){return;}
    callBack->begin();
    if(gl::modelLoader(command_.objectFileName,callBack)){
        callBack->end();
        callBack->saveFile(
			command_.projectObjectFileName,
			info.absolutePath().toLocal8Bit().toStdString()
			);
    }
/* 操作系统自动回收 */
    //delete callBack;

    return;

}

}

int main(int argc,char ** argv){
    if(argc <= 1){
        std::cout<<"projectModel a.obj -tn/-n/-v b.zip  ";
        return -1;
    }
    Command command ;
    if(argc==2){
        command.objectFileName =std::string( argv[1] );
        command.type = Type::Vertex ;
        command.projectObjectFileName = command.objectFileName+".zip";
    }else if(argc==3){
        command.objectFileName =std::string( argv[1] );
        std::string t_(argv[2]);
        if(t_=="-n"){
            command.type = Type::Vertex|Type::Normal;
        }else if(t_=="-v"){
            command.type = Type::Vertex;
        }
        else if(t_=="-tn"){
            command.type = Type::Vertex|
                    Type::Normal|
                    Type::Texture;
		}
		else {
			return -1;
		}
        command.projectObjectFileName = command.objectFileName+".zip";
    }else{
        command.objectFileName =std::string( argv[1] );
        std::string t_(argv[2]);
        if(t_=="-n"){
            command.type = Type::Vertex|Type::Normal;
        }else if(t_=="-v"){
            command.type = Type::Vertex;
        }else if(t_=="-tn"){
            command.type = Type::Vertex|
                    Type::Normal|
                    Type::Texture;
		}
		else {
			return -1;
		}
        command.projectObjectFileName = std::string(argv[3]);
    }


    eval_command(command );

return 0;
}

/* endl */

