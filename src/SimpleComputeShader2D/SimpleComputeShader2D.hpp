/*utf8 with bom*/
#ifndef _0_SimpleComputeShader2D__HPP__0x00
#define _0_SimpleComputeShader2D__HPP__0x00

#include <QGLWidget>

class SimpleComputeShader2D :public QGLWidget {
public:
SimpleComputeShader2D( QWidget * =0 );
~SimpleComputeShader2D();
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

