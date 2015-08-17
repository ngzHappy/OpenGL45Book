/*utf8 with bom*/
#ifndef _0_SingleCube__HPP__0x00
#define _0_SingleCube__HPP__0x00

#include <QGLWidget>

class SingleCube :public QGLWidget {
public:
SingleCube( QWidget * =0 );
~SingleCube();
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

