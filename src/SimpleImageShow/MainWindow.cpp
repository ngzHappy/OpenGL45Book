#include "SimpleImageShow.hpp"
#include <OpenGLTool/QConsoleWidget.hpp>
#include "MainWindow.hpp"
#include <QSplitter>
#include <QHBoxLayout>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *){
    console_ = new QConsole ;
    imageShow_ = new SimpleImageShow;
    QSplitter * splitter = new QSplitter;
    QHBoxLayout * hlayout = new QHBoxLayout;
    this->setLayout(hlayout);
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addWidget(splitter);
    splitter->addWidget(console_ );
    splitter->addWidget(imageShow_ );

    console_->setSizePolicy(
                QSizePolicy(QSizePolicy::MinimumExpanding,
                            QSizePolicy::Expanding)
                );
    console_->setSizePolicy(
                QSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding)
                );

    console_->setMinimumWidth(100);
    console_->setMaximumWidth(220);
    imageShow_->setMinimumWidth(500);
    this->setMinimumHeight(500);

    console_->connect(
                console_,
                console_->getEvalsFunction(),
                [this](QList<QConsoleWidgetCommand > commans){
if(commans.empty()){return;}
this->imageShow_->showImage( commans.begin()->command );
    }
                );
}

MainWindow::~MainWindow(){

}
