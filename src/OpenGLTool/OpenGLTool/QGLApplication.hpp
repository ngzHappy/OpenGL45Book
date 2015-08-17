#ifndef _0_Q_APPKICATION__OPENGL__
#define _0_Q_APPKICATION__OPENGL__

#include <QApplication>
#include <memory>
#include <mutex>
 
class QGLApplication : public QObject {
    Q_OBJECT
public:
    QGLApplication( QApplication * );
	~QGLApplication();

    QApplication * getQApplication(){return app_;}

	typedef std::shared_ptr< std::recursive_mutex > AtomicFunctionType;
	static AtomicFunctionType atomicFunction();
private:
    QApplication * app_ ;
};


#endif


