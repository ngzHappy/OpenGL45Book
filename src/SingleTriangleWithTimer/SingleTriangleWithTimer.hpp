﻿/*utf8 with bom*/
#ifndef _0_SingleTriangleWithTimer__HPP__0x00
#define _0_SingleTriangleWithTimer__HPP__0x00

#include <QGLWidget>

class SingleTriangleWithTimer :public QGLWidget {
public:
SingleTriangleWithTimer( QWidget * =0 );
~SingleTriangleWithTimer();
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

