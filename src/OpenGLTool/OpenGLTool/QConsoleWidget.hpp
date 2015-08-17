#ifndef __Q__CONSOLE__0x00__
#define __Q__CONSOLE__0x00__

#include <QImage>
#include <QList>
#include <QString>
#include <array>
#include <list>


class QAction;
class QMenu;

class    QConsoleWidgetCommand {
public:

	QString command;

};

#include <QTextEdit>
typedef QTextEdit QConsoleWidgetParent ;
class QConsoleWidgetPrivate;
class QConsoleWidget :
        public QConsoleWidgetParent
{
    Q_OBJECT
public:

    explicit QConsoleWidget(QWidget * =0);
	virtual ~QConsoleWidget();

	void setPrompt(const QString &v);
	const QString & getPrompt()const { return prompt_; }
	
	const QTextCharFormat & getInnerCharFormat()const;
	QImage getBackGroundPicture();
	QColor getBackGroundPictureLastColor();

private:
	int promptBeginPos_ = 0;
	int promptEndPos_ = 0;
	bool isEvaling_ = false;
	QString prompt_;
	QList< QConsoleWidgetCommand > commands;
    QConsoleWidgetPrivate * thisp;
	std::array<QAction *, 8 > mouseActions;
	std::array<QMenu *, 5> mouseMenus;
	
	class UnNameFunction;
	template<
		typename ReturnType,
		typename FunctionName= UnNameFunction,
		typename ...Args>
	static ReturnType _pf(QConsoleWidget *,Args...);

	template<
		typename ReturnType,
		typename FunctionName= UnNameFunction,
		typename ...Args>
	static ReturnType _cpf(const QConsoleWidget *, Args...);

protected:
    void showEvent(QShowEvent *) override;
    void resizeEvent(QResizeEvent *e) override;
	void keyPressEvent(QKeyEvent * e) override;
	void mousePressEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent * event);
    void paintEvent(QPaintEvent *e)override;
    void dragEnterEvent(QDragEnterEvent *e)override;
    void dragMoveEvent(QDragMoveEvent *e)override;
    void dropEvent(QDropEvent *e)override;
public slots:
	void begeinEvals();
	void endEvals();
	void updateCharFormat();
public:
	typedef void(QConsoleWidget::*EvalsType)(QList<QConsoleWidgetCommand >);
	typedef QList<QConsoleWidgetCommand > Commands;
	static EvalsType getEvalsFunction() { return &QConsoleWidget::evals ; }
signals:
void evals(QList<QConsoleWidgetCommand >);
 

};


class QConsole : public QWidget {
	Q_OBJECT
public:
	~QConsole();
	explicit QConsole(QWidget * =0);
 
	void insertText(
		const QString &,
		const QTextCharFormat &
		);
	void insertText(const QString &);

private:
	QConsoleWidget * thisp;
protected:
	void paintEvent(QPaintEvent *e)override;
public:
	typedef void(QConsole::*EvalsType)(QList<QConsoleWidgetCommand >);
	typedef QList<QConsoleWidgetCommand > Commands;
	static EvalsType getEvalsFunction() { return &QConsole::evals; }
signals:
void evals(QList<QConsoleWidgetCommand >);

};

#endif
