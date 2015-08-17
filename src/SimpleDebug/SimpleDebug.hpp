﻿
#ifndef _0_SimpleDebug__HPP__0x00
#define _0_SimpleDebug__HPP__0x00

#include <QGLWidget>

class SimpleDebug :public QGLWidget {
public:
SimpleDebug( QWidget * =0 );
~SimpleDebug();
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

