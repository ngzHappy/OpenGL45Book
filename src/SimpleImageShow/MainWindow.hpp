#ifndef __MAIN__WINDOW__S__
#define __MAIN__WINDOW__S__

#include <QWidget>
class QConsole ;
class SimpleImageShow;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow( QWidget * =0 );
    ~MainWindow();
private:
    QConsole  * console_ = 0;
    SimpleImageShow * imageShow_ = 0;
};


#endif


