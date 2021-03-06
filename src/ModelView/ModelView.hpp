﻿/*utf8 with bom*/
#ifndef _0_ModelView__HPP__0x00
#define _0_ModelView__HPP__0x00

#include <QGLWidget>

class ModelView :public QGLWidget {
public:
ModelView( QWidget * =0 );
~ModelView();
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
public slots:
void loadModel(const QString &);
};

#endif

