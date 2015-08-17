#include "test.hpp"

#include <QCoreApplication>

//#the application is just for test ,never run!!!
int main(int argc,char ** argv)try{
    QCoreApplication app(argc,argv);
    throw 12345;
    app.exec();
}catch(...){

}
