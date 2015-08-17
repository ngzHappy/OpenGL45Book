/*utf8 with bom*/
#ifndef _0_SimpleDrawArraysInstancedBaseInstance__HPP__0x00
#define _0_SimpleDrawArraysInstancedBaseInstance__HPP__0x00

#include <QGLWidget>

class SimpleDrawArraysInstancedBaseInstance :public QGLWidget {
public:
SimpleDrawArraysInstancedBaseInstance( QWidget * =0 );
~SimpleDrawArraysInstancedBaseInstance();
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

