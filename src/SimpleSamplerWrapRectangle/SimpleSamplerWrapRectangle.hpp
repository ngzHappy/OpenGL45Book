﻿/*utf8 with bom*/
#ifndef _0_SimpleSamplerWrapRectangle__HPP__0x00
#define _0_SimpleSamplerWrapRectangle__HPP__0x00

#include <QGLWidget>

class SimpleSamplerWrapRectangle :public QGLWidget {
public:
SimpleSamplerWrapRectangle( QWidget * =0 );
~SimpleSamplerWrapRectangle();
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

