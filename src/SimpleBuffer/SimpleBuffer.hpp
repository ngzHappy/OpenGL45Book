
#ifndef _0_SimpleBuffer__HPP__0x00
#define _0_SimpleBuffer__HPP__0x00

#include <QGLWidget>

class SimpleBuffer :public QGLWidget {
public:
SimpleBuffer( QWidget * =0 );
~SimpleBuffer();
private:
class ThisPrivate;
friend class ThisPrivate;
ThisPrivate * thisp = 0;
bool isOpenGLInited = false;
bool isOpenGLPainting = false;
protected:
virtual void paintGL() override;
virtual void initializeGL() override;
virtual void resizeGL(int w, int h)override;
};

#endif

