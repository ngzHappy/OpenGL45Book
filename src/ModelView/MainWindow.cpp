#include "ModelView.hpp"
#include <OpenGLTool/QConsoleWidget.hpp>
#include "MainWindow.hpp"
#include <QSplitter>
#include <QHBoxLayout>
#include <QSizePolicy>

class MainWindow::ThisPrivate {
public:
	MainWindow * super = 0;
	QConsole * console = 0;
	ModelView * modelView = 0;
	QSplitter * splitter = 0;
	ThisPrivate(MainWindow * s):super(s) {
		modelView = new ModelView;
		console = new QConsole;
		splitter = new QSplitter;
		QHBoxLayout * l_ = new QHBoxLayout;
		super->setLayout(l_);
		l_->setMargin(0);
		l_->setSpacing(0);
		l_->addWidget(splitter);
		splitter->addWidget(console);
		splitter->addWidget(modelView);
		super->setMinimumSize({812,600});
		console->setFixedWidth( 222 );

		console->connect(console, console->getEvalsFunction(),
			[this](QList<QConsoleWidgetCommand > fileName_) {
			if (fileName_.empty()) { return; }
			const QString & fileName__ = fileName_.begin()->command ;
			const static constexpr char _[]= R"(file:///)";
			if (fileName__.startsWith(_)) {
				modelView->loadModel(fileName__.mid(sizeof(_)-1));
			}
			else {
				modelView->loadModel(fileName__);
			}
			
		}
			);

	}
};

MainWindow::MainWindow( QWidget * p ):
    QWidget(p){
	thisp = new ThisPrivate(this);
}


MainWindow::~MainWindow(){
	delete thisp;
}









