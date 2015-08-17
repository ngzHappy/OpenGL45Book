#ifndef __MAIN__WINDOW__hpp
#define __MAIN__WINDOW__hpp

#include <QWidget>

class MainWindow :public QWidget {
    Q_OBJECT
public:

    MainWindow( QWidget * =0 );
    ~MainWindow();
private:
	class ThisPrivate;
	friend class ThisPrivate;
	ThisPrivate * thisp = 0;
};

#endif

