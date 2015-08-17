#ifndef __Q__CONSOLE__private0x00__
#define __Q__CONSOLE__private0x00__

#include "QConsoleWidget.hpp"
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <QDebug>
#include <QString>
#include <QTextCharFormat>
#include <QWidget>
#include <QToolButton>
#include <QTextDocument>
#include <QTextBlock>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFontMetricsF>
#include <QTextLayout>
#include <QScrollBar>
#include <utility>
#include <algorithm>
#include <memory>
#include <QMenu>
#include <vector>
#include <boost/circular_buffer.hpp>
#include <QFontDialog>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QHBoxLayout>
#include <QFont>
#include <QColorDialog>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

class CommandBufferManager{
    boost::circular_buffer< QList<QConsoleWidgetCommand> > commandBuffers;
    int currentIndex = -1;
public:
    enum{ SIZE=50 };
    CommandBufferManager()
        :commandBuffers(SIZE){
    }

    QList<QConsoleWidgetCommand> upOne(){
        if(commandBuffers.empty()){return QList<QConsoleWidgetCommand>();}
        ++currentIndex;
        if( currentIndex< size() && currentIndex>=0){
            return commandBuffers[currentIndex  ];
        }else{
            currentIndex= size();
        }
        return *(commandBuffers.rbegin());
    }

    QList<QConsoleWidgetCommand> downOne(){
        if(commandBuffers.empty()){return QList<QConsoleWidgetCommand>();}
        --currentIndex;
        if( currentIndex<size() && currentIndex>=0){
            return commandBuffers[currentIndex  ];
        }else{
            currentIndex=0;
        }
        return commandBuffers[0];
    }

    int size()const{
        return int( commandBuffers.size() );
    }
    void push_back( QList<QConsoleWidgetCommand> cmd ){
        commandBuffers.push_front(cmd);
        resetIndex();
    }
    void resetIndex(){currentIndex=-1;}
};

typedef QToolButton QConsoleWidgetPrivateParent;
class QConsoleWidgetPrivate:
        public QConsoleWidgetPrivateParent{
    Q_OBJECT
public:

    ~QConsoleWidgetPrivate();
    explicit QConsoleWidgetPrivate(QConsoleWidget *,QWidget *  );
    QConsoleWidget * super ;
	float positionX;
	float positionY;
	QTextCharFormat textCharFormat;

	int firstVisibleBlock = -1;
	int vBarValue = -1;
	std::list<QRectF> visibleBlockRects;
	QImage backGroundImage;
	QColor backGroundImageLastColor;
	bool isFirstUpdateBImage = true;

    CommandBufferManager commandBufferManager;
	void enableActions();
	void disableActions();

	QAction * actions[2];

protected:
	void paintEvent(QPaintEvent *e)override;
public slots:
void selectAndSetFont(   );
void selectAndSetFontColor(  );
};


#endif
