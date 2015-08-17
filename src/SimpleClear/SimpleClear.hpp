
#ifndef _0_SimpleClear__HPP__0x00
#define _0_SimpleClear__HPP__0x00

#include <QGLWidget>

class SimpleClear :public QGLWidget {
public:
SimpleClear( QWidget * =0 );
~SimpleClear();
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

