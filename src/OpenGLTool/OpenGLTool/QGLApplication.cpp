#include "QGLApplication.hpp"
#include <cstdlib>
#include <ctime>
#include <QImage>



namespace {
    const static bool rand__ = []() ->bool{
        std::srand( (unsigned int)(std::time(0)) );
        return true;
    }();
}

QGLApplication::~QGLApplication() {
}

namespace  {
static QGLApplication::AtomicFunctionType __atomic__global__lock;
}
QGLApplication::QGLApplication( QApplication * a ):app_(a) {


    const static bool __image__plugins__force__load =[](){
        {QImage temp("null.png");(void)temp;}
        {QImage temp("null.bmp");(void)temp;}
        {QImage temp("null.jpg");(void)temp;}
        {QImage temp("null.jpeg");(void)temp;}
        return bool(rand()&1);
    }();

    if(__atomic__global__lock){return;}
    __atomic__global__lock = QGLApplication::AtomicFunctionType(
                new std::recursive_mutex,
                [](std::recursive_mutex * locker_){
            if(0==locker_){return;}
            while (locker_->try_lock()==false) {}
            locker_->unlock();
}
                );
    (void) __image__plugins__force__load;
}



QGLApplication::AtomicFunctionType 
QGLApplication::atomicFunction() {
QGLApplication::AtomicFunctionType  ans ;
return __atomic__global__lock ;
}
