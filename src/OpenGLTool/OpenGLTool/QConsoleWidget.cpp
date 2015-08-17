#include "QConsoleWidgetPrivate.hpp"

namespace {
	class EnableActions;
	class DisableActions;
}

namespace {
	enum {
		INDEX_SELECT_COPY = 0,//copy()
		INDEX_SELECT_ALL,//selectAll()
		INDEX_READ_SIZE = INDEX_SELECT_ALL,
		INDEX_SELECT_DELET,//clear()
		INDEX_SELECT_CUT,//cut()
		INDEX_SELECT_PASTE,//paste()
		INDEX_ASELECT_PASTE,//paste()
		INDEX_ASELECT_CUT,//cut()
		INDEX_ASELECT_DELET,//delete()
		INDEX_SIZE,
	};
}

namespace  {
QString MenuStyleSheet =
        QString::fromUtf8( u8R"( QMenu{background-color:#BBBBBB; } )" );
}

namespace  {
typedef QConsoleWidgetParent TP;
}

QConsoleWidget::~QConsoleWidget(){}

namespace {
class UpdatePromptWidget;
class UpdatePromptWidgetPositon;
class MoveToEnd;
}

template<> void
QConsoleWidget::_pf<void, UpdatePromptWidgetPositon>(
        QConsoleWidget * thisp
        ) {

    {
        QTextDocument * doc = thisp->document();
        QTextBlock textBlock = doc->findBlock(thisp->promptEndPos_);
        QTextLayout * layout_ = textBlock.layout();
        if (layout_) {
            QPointF pos_ = layout_->position();
            thisp->thisp->positionX = pos_.x();

            if (layout_->lineCount() > 0) {
                thisp->thisp->positionY = pos_.y() +
                        layout_->lineAt(0).leading();
            }
            else {
                thisp->thisp->positionY = pos_.y();
            }

        }
    }

    //TODO: UpdatePromptWidgetPositon
    QScrollBar * sb = thisp->verticalScrollBar();
    int sbv = sb->value();
    sbv = std::max<int>( 0,thisp->thisp->positionY-sbv );

    thisp->thisp->setProperty("pos",
                              QPoint(int(thisp->thisp->positionX),sbv));
}

template<> void 
QConsoleWidget::_pf<void, UpdatePromptWidget>(
        QConsoleWidget * thisp
        ) {
    //TODO: UpdatePromptWidget
    {
        QFontMetricsF fontMetrics(
                    thisp->thisp->textCharFormat.font());
        {
            QTextDocument * doc = thisp->document();
            QTextBlock textBlock =
                    doc->findBlock(thisp->promptEndPos_);
            QTextCursor cursor_(textBlock);
            QTextBlockFormat bf_ = cursor_.blockFormat();

            float fh =
                    fontMetrics.height()
                    +1.55f;
            thisp->thisp->setFixedHeight(fh);
            thisp->thisp->setFixedWidth(fh);
            bf_.setTextIndent(thisp->thisp->width());
            cursor_.setBlockFormat(bf_);
            thisp->setTextCursor(cursor_);

        }
		         
    }
    _pf<void, UpdatePromptWidgetPositon>(thisp);
    thisp->raise();
}

template<> void
QConsoleWidget::_pf<void, MoveToEnd>(
        QConsoleWidget * thisp
        ) {
    //TODO: MoveToEnd
    QTextCursor textCursor = thisp->textCursor();
    textCursor.movePosition(
                QTextCursor::End,
                QTextCursor::MoveAnchor, 0);
    thisp->setTextCursor(textCursor);
}


void QConsoleWidget::setPrompt(const QString &v) {
    //TODO: QConsoleWidget::setPrompt
    {
        prompt_ = v;
        _pf<void, MoveToEnd>(this);
        auto tc_ = this->textCursor();
        if (tc_.columnNumber()) {
            this->insertPlainText("\n");
        }

        promptBeginPos_ = this->textCursor().position();
        this->insertPlainText( getPrompt().simplified() );
        promptEndPos_ = this->textCursor().position();

    }
    _pf<void, UpdatePromptWidget>(this);
    _pf<void, MoveToEnd>(this);
}

QConsoleWidgetPrivate::~QConsoleWidgetPrivate(){}

QConsoleWidgetPrivate::QConsoleWidgetPrivate(
        QConsoleWidget *s,QWidget *p
        ):
    QConsoleWidgetPrivateParent(p)
{
    super = s;
    positionX = 0;
    positionY = 0;
    {//TODO: font menu
        QMenu * menu = new QMenu(this);
        this->setMenu(menu);
        menu->setStyleSheet( MenuStyleSheet );
        this->setPopupMode(QToolButton::InstantPopup);
        typedef void(QAction::*AT)(bool);
        {
            QAction * action =
                    new QAction( trUtf8(u8"选择字体"), this);
            action->connect(action, AT(&QAction::triggered ),
                            [this](bool) { 
				selectAndSetFont(); }
            );
            menu->addAction(action);
			actions[0] = action;
        }
		{
			QAction * action =
				new QAction(trUtf8(u8"选择字体颜色"), this);
			action->connect(action, AT(&QAction::triggered),
				[this](bool) {
				selectAndSetFontColor(); }
			);
			actions[1] = action;
			menu->addAction(action);
		}
    }
}


void QConsoleWidget::resizeEvent(QResizeEvent *e) {
    QConsoleWidgetParent::resizeEvent(e);
    _pf<void, UpdatePromptWidgetPositon>(this);
}

namespace {
class InitActions;
class InitMenus;
class UpdateAfterEditorBlockFormat;
class UpdateAfterEditorBlock;
}

void QConsoleWidgetPrivate::
enableActions() {
	for (auto i : actions) { i->setEnabled(true); }
}

void QConsoleWidgetPrivate::
disableActions() {
	for (auto i : actions) { i->setEnabled(false); }
}

template<> void
QConsoleWidget::_pf<void, EnableActions>(
	QConsoleWidget * thisp
	) {
	for (auto i : thisp->mouseActions) {
		i->setEnabled(true);
	}
	thisp->thisp->enableActions();
}

template<> void
QConsoleWidget::_pf<void, DisableActions>(
	QConsoleWidget * thisp
	) {
	//?????
	for (auto i : thisp->mouseActions) {
		i->setEnabled(false);
	}
	thisp->thisp->disableActions();
}

template<> void
QConsoleWidget::_pf<void, UpdateAfterEditorBlockFormat>(
        QConsoleWidget * thisp
        ) {
    //TODO: UpdateAfterEditorBlockFormat
    auto doc_ = thisp->document();
    auto block_ = doc_->findBlock(thisp->promptEndPos_);
    block_ = block_.next();
    while (block_.isValid()){
        {
            QTextCursor cursor_(block_);
            cursor_.setPosition(block_.position());
            cursor_.select(QTextCursor::BlockUnderCursor);
            cursor_.mergeCharFormat(thisp->thisp->textCharFormat);
            thisp->setTextCursor(cursor_);
        }
        {
            QTextCursor cursor_(block_);
            auto bf_ = cursor_.blockFormat();
            bf_.setTextIndent(0);
            cursor_.setBlockFormat(bf_);
            thisp->setTextCursor(cursor_);
            block_ = block_.next();
        }
    }

}

namespace {
//void	redo()
//void	undo()
	
enum {
    INDEX_MENU_SELECT_RW,
    INDEX_MENU_SELECT_R,
    INDEX_MENU_SELECT_A,
    INDEX_MENU_R,
    INDEX_MENU_RW,
};
}

template<> void
QConsoleWidget::_pf<void, InitMenus>(
        QConsoleWidget * thisp) {
    //TODO: init menus
    auto & mms_ = thisp->mouseMenus;
    auto & mas_ = thisp->mouseActions;

    for (auto & i : mms_) {
        i = new QMenu(thisp);
        i->setStyleSheet( MenuStyleSheet );
    }

    {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_SELECT_RW];
        menu->addAction(mas_[INDEX_SELECT_COPY]);
        menu->addAction(mas_[INDEX_SELECT_ALL]);
        menu->addAction(mas_[INDEX_SELECT_DELET]);
        menu->addAction(mas_[INDEX_SELECT_CUT]);
        menu->addAction(mas_[INDEX_SELECT_PASTE]);
    }
    {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_SELECT_R];
        menu->addAction(mas_[INDEX_SELECT_COPY]);
        menu->addAction(mas_[INDEX_SELECT_ALL]);
    }
    {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_SELECT_A];
        menu->addAction(mas_[INDEX_SELECT_COPY]);
        menu->addAction(mas_[INDEX_SELECT_ALL]);
        menu->addAction(mas_[INDEX_ASELECT_DELET]);
        menu->addAction(mas_[INDEX_ASELECT_CUT]);
        menu->addAction(mas_[INDEX_ASELECT_PASTE]);
    }
    {
        QMenu * menu = mms_[INDEX_MENU_R ];
        menu->addAction(mas_[INDEX_SELECT_ALL]);
    }
    {
        QMenu * menu = mms_[INDEX_MENU_RW];
        menu->addAction(mas_[INDEX_SELECT_ALL]);
        menu->addAction(mas_[INDEX_SELECT_PASTE]);
    }
}

namespace {
class ResetSelect  ;
}
template<> void
QConsoleWidget::_pf<void, ResetSelect>(
        QConsoleWidget * _thisp) {
    QTextCursor textCursor = _thisp->textCursor();
    auto epos = textCursor.selectionEnd();
    textCursor.setPosition(_thisp->promptEndPos_);
    textCursor.setPosition(epos, QTextCursor::KeepAnchor);
    _thisp->setTextCursor(textCursor);
};

template<> void
QConsoleWidget::_pf<void, InitActions>(
        QConsoleWidget * thisp) {

    //TODO: inin mouse actions
    static const QString cut_ = trUtf8(u8"剪贴");
    static const QString paste_ = trUtf8(u8"粘贴");
    static const QString delect_ = trUtf8(u8"删除");
    auto & mas_ = thisp->mouseActions;
    mas_[INDEX_SELECT_COPY]   =
            new QAction(trUtf8(u8"复制"),thisp);
    mas_[INDEX_SELECT_ALL] =
            new QAction(trUtf8(u8"全选"), thisp);
    mas_[INDEX_SELECT_DELET] =
            new QAction(delect_, thisp);
    mas_[INDEX_SELECT_CUT] =
            new QAction(cut_, thisp);
    mas_[INDEX_SELECT_PASTE] =
            new QAction(paste_, thisp);
    mas_[INDEX_ASELECT_DELET] =
            new QAction(delect_, thisp);
    mas_[INDEX_ASELECT_CUT] =
            new QAction(cut_, thisp);
    mas_[INDEX_ASELECT_PASTE] =
            new QAction(paste_, thisp);

    typedef void(QAction::*AT)(bool);
    mas_[INDEX_SELECT_ALL]->connect(
                mas_[INDEX_SELECT_ALL], AT(&QAction::triggered),
                [thisp](bool) {thisp->selectAll(); }
    );
    mas_[INDEX_SELECT_COPY]->connect(
                mas_[INDEX_SELECT_COPY], AT(&QAction::triggered),
                [thisp](bool) {thisp->copy(); }
    );
    mas_[INDEX_SELECT_DELET]->connect(
                mas_[INDEX_SELECT_DELET], AT(&QAction::triggered),
                [thisp](bool) {
        auto tc = thisp->textCursor();
        tc.removeSelectedText();
        thisp->setTextCursor(tc);
    }
    );
    mas_[INDEX_SELECT_CUT]->connect(
                mas_[INDEX_SELECT_CUT], AT(&QAction::triggered),
                [thisp](bool) {thisp->cut(); }
    );
    mas_[INDEX_SELECT_PASTE]->connect(
                mas_[INDEX_SELECT_PASTE], AT(&QAction::triggered),
                [thisp](bool) {thisp->paste();  }
    );
    mas_[INDEX_ASELECT_DELET]->connect(
                mas_[INDEX_ASELECT_DELET], AT(&QAction::triggered),
                [thisp](bool) {
        _pf<void, ResetSelect>(thisp);
        auto tc = thisp->textCursor();
        tc.removeSelectedText();
        thisp->setTextCursor(tc);
    }
    );
    mas_[INDEX_ASELECT_CUT]->connect(
                mas_[INDEX_ASELECT_CUT], AT(&QAction::triggered),
                [thisp](bool) {
        _pf<void, ResetSelect>(thisp);
        thisp->cut();
    }
    );
    mas_[INDEX_ASELECT_PASTE]->connect(
                mas_[INDEX_ASELECT_PASTE], AT(&QAction::triggered),
                [thisp](bool) {
        _pf<void, ResetSelect>(thisp);
        thisp->paste();
    }
    );

}

QConsoleWidget::QConsoleWidget(QWidget * p) :TP(p) {
     thisp = new QConsoleWidgetPrivate(this, this);
    /* 背景透明 */
    this->setFrameStyle(QFrame::NoFrame);
     TP::setStyleSheet(
                 "background-color:rgba(0,0,0,0);"
                 "border-color:#00000000;"
                 );

    {
        QTextCursor _cursor = this->textCursor();
        thisp->textCharFormat =
                _cursor.charFormat() ;
        thisp->textCharFormat.setForeground( QColor(0,0,0,255) );
        _cursor.setCharFormat( thisp->textCharFormat );
        this->setTextCursor( _cursor );
    }

    this->setMinimumHeight(32);
    /* 禁用redo undo */
    this->setUndoRedoEnabled(false);


    static_assert(
                INDEX_SIZE == sizeof(mouseActions) / sizeof(void *),
                "");


    _pf<void, InitActions>(this);
    _pf<void, InitMenus>(this);

    setPrompt(">>>");
    thisp->raise();

    /*  */
    {//信号槽连接,更新按钮位置
        auto vsb = this->verticalScrollBar();
        typedef void(QScrollBar::* TT)(int);
        vsb->connect(vsb,TT(&QScrollBar::valueChanged),
                     [this](int) {
            _pf<void, UpdatePromptWidgetPositon>(this);
        }
        );
    }

    {//信号槽连接,更新format
        //void	blockCountChanged(int newBlockCount)
        auto doc_ = this->document();
        typedef void(QTextDocument::*DT)(int);
        doc_->connect(doc_,DT(&QTextDocument::blockCountChanged),
                      [this](int) {
            if (isEvaling_) { return; }
            this->updateCharFormat();//
        });
    }

    _pf<void, MoveToEnd>(this);
    /* 开启redo undo */
    this->setUndoRedoEnabled(true);


}

void QConsoleWidget::showEvent(QShowEvent *e){
    TP::showEvent(e);
    _pf<void, UpdatePromptWidget>(this);
    _pf<void, MoveToEnd>(this);
}

namespace {
class KeyPressedAll;
class KeyPressedReadOnly;
class KeyPressedReadWrite;
class SelectKeyPressedAll;
class SelectKeyPressedReadOnly;
class SelectKeyPressedReadWrite;
}


/* 在不可编辑区域按下键盘 */
template<> bool
QConsoleWidget::_pf<bool, KeyPressedReadOnly>(
        QConsoleWidget * thisp,
        QKeyEvent * e) {
    auto key_ = e->key();

    switch (key_)
    {
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_CapsLock:
    case Qt::Key_NumLock:
    case Qt::Key_ScrollLock:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
    case Qt::Key_Home:
    case Qt::Key_End:return false;
    }

    if ( e->modifiers() & Qt::ControlModifier) {
        switch ( key_)
        {
        case Qt::Key_C:
        case Qt::Key_A:return false;
        }
    }

    _pf<void, MoveToEnd>(thisp);
    if (key_== Qt::Key_Backspace) {
        return true;
    }

    return false;
}

namespace  {
class IsInEditorFirstLine;
class IsInEditorLastLine;
class SetToCommand;
}

template<> bool
QConsoleWidget::_pf<bool, IsInEditorFirstLine>(
        QConsoleWidget * thisp ) {
    auto doc_   = thisp->document();
    auto block_ = doc_->findBlock( thisp->promptEndPos_ );
    auto tpos   = thisp->textCursor().position();
    if (block_.contains(tpos) == false) { return false; }
    auto blayout = block_.layout();
    if (blayout) {
        if (blayout->lineCount()) {
            auto line0 = blayout->lineAt(0);
            auto line1 = 
				blayout->lineForTextPosition(tpos-block_.position());
            return ( line0.lineNumber() == line1.lineNumber() );
        }
    }
    return false;
}

template<> bool
QConsoleWidget::_pf<bool, IsInEditorLastLine>(
        QConsoleWidget *  thisp) {
    auto doc_ = thisp->document();
    auto block_ = doc_->lastBlock();
    auto tpos = thisp->textCursor().position();
    if (block_.contains(tpos) == false) { return false; }
    auto blayout = block_.layout();
    if (blayout) {
        if (blayout->lineCount()) {
            auto line0 = blayout->lineAt(blayout->lineCount()-1);
            auto line1 = 
				blayout->lineForTextPosition(tpos - block_.position());
            return (line0.lineNumber() == line1.lineNumber());
        }
    }
    return false;
}

template<> void
QConsoleWidget::_pf<void, SetToCommand>(
        QConsoleWidget * thisp,QList<QConsoleWidgetCommand> command ) {
    //TODO: ...
    auto tc = thisp->textCursor();
    tc.setPosition( thisp->promptEndPos_);
    tc.movePosition(QTextCursor::End, QTextCursor::KeepAnchor,0);
    thisp->setTextCursor( tc );

    if ( command.empty() ) {
        tc.removeSelectedText();
        thisp->setTextCursor(tc);
    }

    auto tryAddReturn = [](const QString & str)->QString {
        if (str.isEmpty()) { return str; }
        if (str.endsWith("\n")) { return str; }
        return (str + "\n");
    };

    if (command.size()==1 ) {
        thisp->insertPlainText(  command.begin()->command );
    }
    else if (command.size() == 2) {
        auto b0 = command.begin();
        auto b1 = b0 + 1;
        if (b1->command.isEmpty()) {
            thisp->insertPlainText(b0->command);
        }
        else {
            thisp->insertPlainText(tryAddReturn(b0->command));
            thisp->insertPlainText(b1->command);
        }
    }
    else {

        auto b = command.begin();
        auto e = command.end() - 2;

        for (;b!=e;++b ) {
            const QString & temp = tryAddReturn( b->command );
            if (temp.isEmpty() == false) {
                thisp->insertPlainText(temp);
            }
        }

        b = e;
        e = e + 1;

        if (e->command.isEmpty()) {
            thisp->insertPlainText(b->command);
        }
        else {
            thisp->insertPlainText(tryAddReturn(b->command));
            thisp->insertPlainText(e->command);
        }

    }

}


/* 在可编辑区域按下键盘 */
template<> bool
QConsoleWidget::_pf<bool, KeyPressedReadWrite>(
        QConsoleWidget * thisp,
        QKeyEvent * e) {
    auto key_ = e->key();

    auto isInEditorFirstLine=[](QConsoleWidget * thisp)->bool{
        return _pf<bool, IsInEditorFirstLine>(thisp);
    };
    auto isInEditorLastLine=[](QConsoleWidget * thisp)->bool{
        return _pf<bool, IsInEditorLastLine>(thisp);
    };
    auto setToCommand=[](QConsoleWidget * thisp,QList<QConsoleWidgetCommand> command )->void{
        return _pf<void, SetToCommand>(thisp,command );
    };

    switch (key_){
    //TODO: key up
    case Qt::Key_Up:{
        if(isInEditorFirstLine(thisp)){
            auto temp = thisp->thisp->commandBufferManager.upOne();
            setToCommand(thisp,temp);
            {
                auto tc = thisp->textCursor();
                tc.setPosition(thisp->promptEndPos_);
                thisp->setTextCursor(tc);
            }
            return true;
        }
        return false;
    }
    case Qt::Key_Down:{
        if(isInEditorLastLine(thisp)){
            auto temp = thisp->thisp->commandBufferManager.downOne();
            setToCommand(thisp,temp);
            _pf<void, MoveToEnd>(thisp);
            return true;
        }
        return false;
    }
    case Qt::Key_Left: {
        auto tc = thisp->textCursor();
        auto pos_ = tc.position();
        if (pos_ <= thisp->promptEndPos_) { return true; }
    }
    }

    //Backspace
    //Delete
    {
        if (key_ == Qt::Key_Backspace) {
            auto tc = thisp->textCursor();
            if (tc.position() == thisp->promptEndPos_) { return true; }
        }
    }

    {//TODO: evals
        if (key_==Qt::Key_Return) {
            if (e->modifiers()==0) {

				class EvalsLock {
					QConsoleWidget * __this;
				public :
					EvalsLock(QConsoleWidget *t):__this(t) {
						__this->begeinEvals();
					}
					~EvalsLock() {
						__this->endEvals();
					}
				}_evalsLock(thisp);
                
                thisp->evals(thisp->commands);
                thisp->thisp->commandBufferManager.\
                        push_back(thisp->commands) ;
                
                thisp->thisp->isFirstUpdateBImage = false;
                return true;
            }
            else {
                thisp->insertPlainText("\n");
                return true;
            }
        }
    }

    thisp->TP::keyPressEvent(e);
    return true;
}

template<> bool
QConsoleWidget::_pf<bool, SelectKeyPressedAll>(
        QConsoleWidget * thisp,
        QKeyEvent * e) {

    auto resetSelect = [](QConsoleWidget * _thisp)->void{
        QTextCursor textCursor = _thisp->textCursor();
        auto epos = textCursor.selectionEnd();
        textCursor.setPosition( _thisp->promptEndPos_);
        textCursor.setPosition( epos, QTextCursor::KeepAnchor);
        _thisp->setTextCursor(textCursor);
    };

    auto key_ = e->key();

    switch (key_)
    {
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_CapsLock:
    case Qt::Key_NumLock:
    case Qt::Key_ScrollLock:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
    case Qt::Key_Home:
    case Qt::Key_End:return false;
    }

    if (e->modifiers() & Qt::ControlModifier) {
        switch (key_)
        {
        case Qt::Key_C:
        case Qt::Key_A:return false;
        case Qt::Key_X:/*剪贴*/ {
            class EventKey :public QKeyEvent {
            public:
                void setKey() { k = Qt::Key_C; }
            };
            EventKey * fk = (EventKey*)(e);
            fk->setKey();
            thisp->TP::keyPressEvent(fk);
            resetSelect(thisp);
            QTextCursor textCursor = thisp->textCursor();
            textCursor.removeSelectedText();
            thisp->setTextCursor(textCursor);
            return true;
        }
        }
    }

    resetSelect(thisp);

    return false;
}

template<> bool
QConsoleWidget::_pf<bool, SelectKeyPressedReadOnly>(
        QConsoleWidget * thisp,
        QKeyEvent * e) {

    auto key_ = e->key();

    switch (key_)
    {
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_CapsLock:
    case Qt::Key_NumLock:
    case Qt::Key_ScrollLock:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
    case Qt::Key_Home:
    case Qt::Key_End:return false;
    }

    if (e->modifiers() & Qt::ControlModifier) {
        switch (key_)
        {
        case Qt::Key_C:
        case Qt::Key_A:return false;
        }
    }

    /*设置为readonly模式*/
    class OnlyRead {
    public:
        QConsoleWidget * __this;
        OnlyRead(QConsoleWidget * s):__this(s) {
            __this->setReadOnly(true);
        }
        ~OnlyRead() {
            __this->setReadOnly(false);
        }
    };

    if (key_==Qt::Key_Backspace) {
        OnlyRead readOnly(thisp);
        _pf<void, MoveToEnd>(thisp);
        thisp->TP::keyPressEvent(e);
    }
    else {
        _pf<void, MoveToEnd>(thisp);
        thisp->TP::keyPressEvent(e);
    }

    return true;
}

/* 选中模式下编辑 */
template<> bool
QConsoleWidget::_pf<bool, SelectKeyPressedReadWrite>(
        QConsoleWidget * /*thisp*/,
        QKeyEvent * /*e*/) {
    return false;
}

namespace {
	class IsEvalingKeyPressed;
	}

template<> bool
QConsoleWidget::_pf<bool, IsEvalingKeyPressed>(
	QConsoleWidget * ,
	QKeyEvent * e) {
	/* 在运行模式下只支持少量按键 */
	auto key_ = e->key();

	switch (key_)
	{
	case Qt::Key_Shift:
	case Qt::Key_Control:
	case Qt::Key_Meta:
	case Qt::Key_Alt:
	case Qt::Key_CapsLock:
	case Qt::Key_NumLock:
	case Qt::Key_ScrollLock:
	case Qt::Key_Up:
	case Qt::Key_Down:
	case Qt::Key_Left:
	case Qt::Key_Right:
	case Qt::Key_PageDown:
	case Qt::Key_PageUp:
	case Qt::Key_Home:
	case Qt::Key_End:return false;
	}

	if (e->modifiers() & Qt::ControlModifier) {
		switch (key_)
		{
		case Qt::Key_C:
		case Qt::Key_A:return false;
		}
	}

	return true;
}

void QConsoleWidget::keyPressEvent(QKeyEvent * e) 
{
	if (isEvaling_) {
		if (_pf<bool, IsEvalingKeyPressed>(this,e)) {
			return;
		}
		else {
			return TP::keyPressEvent(e);
		}
	}

    int eval_index  ;
	bool haveDone_;
    {
        QTextCursor tc = this->textCursor();
        if (tc.hasSelection()) {
            auto se = tc.selectionEnd();
            auto sb = tc.selectionStart();
            if (sb >= promptEndPos_) { eval_index = 0; }
            else if (se <= promptEndPos_) { eval_index = 1; }
            else {
                eval_index = 2;
            }
        }
        else {
            auto s = tc.position();
            if (s>= promptEndPos_) {
                eval_index = 3;
            }
            else {
                eval_index = 4;
            }
        }
    }

    switch (eval_index)
    {
    case 0:haveDone_ = _pf<bool, SelectKeyPressedReadWrite>(this, e);  break;
    case 1:haveDone_ = _pf<bool, SelectKeyPressedReadOnly>(this, e);  break;
    case 2:haveDone_ = _pf<bool, SelectKeyPressedAll>(this, e);  break;
    case 3:haveDone_ = _pf<bool, KeyPressedReadWrite>(this, e);  break;
    case 4:haveDone_ = _pf<bool, KeyPressedReadOnly>(this, e);  break;
    }

    if (haveDone_) { return; }
    return TP::keyPressEvent(e);

}


void QConsoleWidget::begeinEvals() {
    isEvaling_ = true;
    {
		_pf<void, DisableActions>(this);
        commands.clear();
        auto doc_ = this->document();
        doc_->clearUndoRedoStacks();
        this->setUndoRedoEnabled(false);
        auto block_ = doc_->findBlock( this->promptEndPos_ );
        {
            QConsoleWidgetCommand command_;
            command_.command =
                    block_.text().mid( prompt_.size() );
            commands.push_back(std::move(command_));
            block_ = block_.next();
        }
        while (block_.isValid()){
            QConsoleWidgetCommand command_;
            command_.command = block_.text();
            commands.push_back( std::move(command_) );
            block_=block_.next();
        }
    }

    {
        QTextCursor tc_ = this->textCursor();
        if (tc_.hasSelection()) { tc_.clearSelection(); }
        this->setTextCursor(tc_);
    }

    QConsoleWidget::_pf<void, MoveToEnd>(this);

    {
        QTextCursor tc_ = this->textCursor();
        tc_.insertText("\n");
        auto bf_ = tc_.blockFormat();
        bf_.setTextIndent(0);
        tc_.setBlockFormat(bf_);
        this->setTextCursor(tc_);
    }

}
void QConsoleWidget::endEvals() {
    isEvaling_ = false;
    {//: getall command information here
        auto doc_ = this->document();
        doc_->clearUndoRedoStacks();
        auto block_ = doc_->findBlock(this->promptEndPos_);
        QTextCursor tc_(block_);
        auto bf_ = block_.blockFormat();
        bf_.setTextIndent(0);
        tc_.setBlockFormat(bf_);
        this->setTextCursor(tc_);
    }
    setPrompt( getPrompt() );
    this->setUndoRedoEnabled(true);
	_pf<void, EnableActions>(this);
}

namespace {
class MousePressedAll;
class MousePressedReadOnly;
class MousePressedReadWrite;
class SelectMousePressedAll;
class SelectMousePressedReadOnly;
class SelectMousePressedReadWrite;
}

template<> bool
QConsoleWidget::_pf<
bool, SelectMousePressedAll
>(
        QConsoleWidget * thisp,
        QMouseEvent * e) {

    if (e->button() & Qt::RightButton) {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_SELECT_A];
        menu->exec(e->globalPos());
        return true;
    }

    return false;
}

template<> bool
QConsoleWidget::_pf<
bool, MousePressedReadOnly
>(
        QConsoleWidget * thisp,
        QMouseEvent * e) {
    //TODO: mr
    if (e->button() & Qt::LeftButton) {
        return false;
    }

    if (e->button() & Qt::RightButton) {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_R ];
        menu->exec(e->globalPos());
        return true;
    }

    return true;
}

template<> bool
QConsoleWidget::_pf<
bool, MousePressedReadWrite
>(
        QConsoleWidget * thisp,
        QMouseEvent * e) {

    if (e->button() & Qt::LeftButton) {
        return false;
    }

    if (e->button() & Qt::RightButton) {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_RW];
        menu->exec(e->globalPos());
        return true;
    }

    return true;
}

template<> bool
QConsoleWidget::_pf<
bool, SelectMousePressedReadWrite
>(
        QConsoleWidget * thisp,
        QMouseEvent * e) {

    if (e->button() & Qt::RightButton) {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_SELECT_RW];
        menu->exec( e->globalPos() );
        return true;
    }

    return false;
}

template<> bool
QConsoleWidget::_pf<
bool, SelectMousePressedReadOnly
>(
        QConsoleWidget * thisp,
        QMouseEvent * e) {

    if (e->button() & Qt::RightButton) {
        QMenu * menu = thisp->mouseMenus[INDEX_MENU_SELECT_R ];
        menu->exec(e->globalPos());
        return true;
    }

    return false;
}

void QConsoleWidget::mousePressEvent(
        QMouseEvent *e
        ) {
    //TODO: mousepressevent

    int eval_index;
    bool haveDone_;

    {
        QTextCursor tc = this->textCursor();
        if (tc.hasSelection()) {
            auto se = tc.selectionEnd();
            auto sb = tc.selectionStart();
            if (sb >= promptEndPos_) { eval_index = 0;/*rw*/ }
            else if (se <= promptEndPos_) { eval_index = 1;/*r*/ }
            else {
                eval_index = 2/*a*/;
            }
        }
        else {
            if (e->button()&Qt::RightButton) {
                auto tc_ = this->cursorForPosition(e->pos());
                this->setTextCursor(tc_);
            }
            auto pos_ =  tc.position();
            if (pos_>=this->promptEndPos_) {
                eval_index = 3;//read write
            }
            else {
                if (pos_>=this->promptBeginPos_) {
                    QTextCursor tc = this->textCursor();
                    tc.setPosition( this->promptEndPos_ );
                    this->setTextCursor(tc);
                    eval_index = 3;//read write
                }
                else {
                    eval_index = 4;//read only
                }
            }
        }
    }

    switch (eval_index)
    {
    case 0: haveDone_ = _pf<bool, SelectMousePressedReadWrite>(this,e); break;
    case 1: haveDone_ = _pf<bool, SelectMousePressedReadOnly>(this, e); break;
    case 2: haveDone_ = _pf<bool, SelectMousePressedAll>(this, e); break;
    case 3: haveDone_ = _pf<bool, MousePressedReadWrite>(this, e); break;
    case 4: haveDone_ = _pf<bool, MousePressedReadOnly>(this, e); break;
    }

    if (haveDone_) { return; }
    return TP::mousePressEvent(e);
}

void QConsoleWidget::\
contextMenuEvent(QContextMenuEvent *  ){/*直接忽略*/}

namespace {
class GetVisibleRect;
class GetVisibleBlock;
}

template<> std::list<QRectF>
QConsoleWidget::_cpf<std::list<QRectF>, GetVisibleBlock>
(const QConsoleWidget * thisp, int & blockNum  ) {
    std::list<QRectF> ans;

    const float vwidth =
            thisp->document()->documentMargin()*2
            +(thisp->thisp->isFirstUpdateBImage?100:0)
            ;

    const auto size_this = thisp->size();

    QTextBlock block_ = thisp->document()->firstBlock();

    if (thisp->document()->blockCount() > 10) {
        int xy = int(0.5 + thisp->document()->documentMargin());
        QTextCursor tc =
                thisp->cursorForPosition(QPoint(xy, xy));
        block_ = tc.block();
        if (false == block_.isValid()) {
            return ans;
        }
    }

    blockNum = block_.blockNumber();

    QRectF vRect = QRectF(
                QPointF(
                    block_.layout()->position().x() ,
                    thisp->verticalScrollBar()->value()-10
                    ),
                QSizeF(
                    size_this.width(),
                    size_this.height()+20
                    )
                );

    while ( block_.isValid() ){
        auto br = block_.layout()->boundingRect();
        br = QRectF(
                    block_.layout()->position(),
                    QSizeF(
                        br.width() + vwidth,
                        br.height()
                        )
                    );
        if (br.intersected(vRect).width()>0) {
            ans.push_back(br);
        }
        else {
            break;
        }
        block_ = block_.next();

    }

    return std::move(ans);
}

void QConsoleWidget::paintEvent(QPaintEvent *e){
    TP::paintEvent(e);
}

QConsole::~QConsole() {}
QConsole::QConsole(QWidget *p) :
    QWidget(p){
    this->setMinimumHeight(200);
    this->setMinimumWidth(100);
    thisp = new QConsoleWidget;

    QHBoxLayout * l = new QHBoxLayout;
    this->setLayout(l);
    l->setMargin(0);
    l->setSpacing(0);
    l->addWidget(thisp);
    this->resize(200,300);
	this->connect(
		thisp,thisp->getEvalsFunction(),
		this,this->getEvalsFunction()
		);
}

void QConsoleWidgetPrivate::
paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setBrush(QColor(255,122,32));
    painter.setPen(QColor(255, 122, 32,0));
    painter.drawRect(this->rect());
}
QColor QConsoleWidget::getBackGroundPictureLastColor() {
	return thisp->backGroundImageLastColor;
}
QImage QConsoleWidget::getBackGroundPicture() {
    int blockNum = -1;
    int width_ = this->width();
    const int height_ = this->height();
    const QBrush brush0(QColor(111,111,111,50));
    const QBrush brush1(QColor(222,222,222,50));
    const auto vRects =
            _cpf<std::list<QRectF>, GetVisibleBlock,int &>(this, blockNum);

    QImage image( this->size(),
                  QImage::Format_RGBA8888_Premultiplied );
    image.fill(QColor(0,0,0,0));
    QPainter painter(&image);
    if (blockNum < 0) { return image; }
    if (vRects.empty()) { return image; }

    {
        bool needR = false;

        if (
                (thisp->firstVisibleBlock == blockNum)&&
                (thisp->vBarValue==verticalScrollBar()->value())
                ) {
            if (thisp->visibleBlockRects.size()== vRects.size()) {
                auto sz = thisp->visibleBlockRects.size();
                auto b0 = thisp->visibleBlockRects.cbegin();
                auto b1 = vRects.cbegin();
                for (decltype(sz) i = 0; i < sz;++i ) {
                    if ((*b0) != (*b1)) {
                        needR = true;
                        break;
                    }
                }
            }
            else {
                needR = true;
            }
        }
        else {
            needR = true;
        }

        if (needR == false) {
            return thisp->backGroundImage;
        }
        else {
            thisp->firstVisibleBlock = blockNum;
        }
    }

    width_ = std::min<int>(width_,int(vRects.begin()->width()));
    double py =
            this->verticalScrollBar()->value() ;
    double havePaint = 0;
    painter.setPen(QColor(11,111,111,0 ));
    for (const QRectF & r: vRects) {
        if (py > r.bottom()) { ++blockNum; continue; }
        double aboutToDraw = r.bottom() - py    ;

        if (blockNum&1) {
			thisp->backGroundImageLastColor = brush1.color();
            painter.fillRect(0, int(havePaint), width_, int(aboutToDraw),
                             brush1);
        }
        else {
			thisp->backGroundImageLastColor = brush0.color();
            painter.fillRect(
				0, int(havePaint), width_, 
				int(aboutToDraw),
                 brush0);
        }
        ++blockNum;
        py += aboutToDraw;
        havePaint += aboutToDraw;
        if (havePaint > height_) { break; }
    }

    if (havePaint<height_) {
        if (blockNum & 1) {
			thisp->backGroundImageLastColor = brush0.color();
            painter.fillRect(
                0, int(havePaint), width_, 
				int(height_- havePaint),
                        brush0);
        }
        else {
			thisp->backGroundImageLastColor = brush1.color();
            painter.fillRect(
                0, int(havePaint), width_, 
				int(height_ - havePaint),
                        brush1);
        }
    }

    thisp->vBarValue = verticalScrollBar()->value();
    thisp->visibleBlockRects = vRects;
    thisp->backGroundImage = image;
    return image;
}

void QConsole::
paintEvent(QPaintEvent * ) {
    QImage image = thisp->getBackGroundPicture();
	if (image.height()>=this->height()) {
		QPainter painter(this);
		painter.drawImage(0, 0, image);
	}
	else {
		QPainter painter(this);
		painter.drawImage(0, 0, image);
		painter.fillRect(
			0, image.height(),
			image.width(), this->height() - image.height() ,
			thisp->getBackGroundPictureLastColor()
			);
	}
    
}

namespace {
class UpdateOnEditorBlockFormat;
}

template<> void
QConsoleWidget::_pf<void, UpdateOnEditorBlockFormat>(
        QConsoleWidget * thisp
        ) {
    auto doc_ = thisp->document();
    auto block_ = doc_->findBlock(thisp->promptEndPos_);
    if(block_.isValid()) {
        {
            QTextCursor cursor_(block_);
            cursor_.setPosition(thisp->promptEndPos_);
            cursor_.select(QTextCursor::BlockUnderCursor);
            cursor_.mergeCharFormat(thisp->thisp->textCharFormat);
            thisp->setTextCursor(cursor_);
        }
        {
            QTextCursor cursor_(block_);
            auto bf_ = cursor_.blockFormat();
            bf_.setTextIndent(thisp->thisp->width());
            cursor_.setBlockFormat(bf_);
            thisp->setTextCursor(cursor_);
        }
    }
    else {
        return;
    }
    _pf<void, UpdatePromptWidget>(thisp);
    _pf<void, MoveToEnd>(thisp);
}

void QConsoleWidget::updateCharFormat(){
    {
        auto tc = this->textCursor();
        tc.clearSelection();
        this->setTextCursor(tc);
    }
    _pf<void, UpdateAfterEditorBlockFormat>(this);
    _pf<void, UpdateOnEditorBlockFormat>(this);
    {
        this->setCurrentCharFormat(thisp->textCharFormat);
    }
}

void QConsoleWidgetPrivate::
selectAndSetFont() {
    auto font_ = this->textCharFormat.font() ;
	
	QFontDialog * dialog = new QFontDialog( font_ );
	if (dialog->exec()) {
		font_ = dialog->selectedFont();
		this->textCharFormat.setFont(font_);
		super->updateCharFormat();
		dialog->deleteLater();
	}
	else {
		dialog->deleteLater();
	}

	firstVisibleBlock = -100;
	super->viewport()->update();
}

void QConsoleWidgetPrivate::
selectAndSetFontColor() {

	auto color_ = 
		this->textCharFormat.foreground().color();

	QColorDialog * dialog = new QColorDialog(color_);
	if (dialog->exec()) {
		color_ = dialog->selectedColor();
		this->textCharFormat.setForeground(color_);
		super->updateCharFormat();
	}
	
	dialog->deleteLater();
	 
}

void QConsole::insertText(
	const QString & t,
	const QTextCharFormat & f
	) {
	{
		auto tc = thisp->textCursor();
		tc.clearSelection();
		thisp->setTextCursor(tc);
	}
	auto tc = thisp->textCursor();
	tc.setCharFormat(f);
	tc.insertText(t);
	thisp->setTextCursor(tc);
}

const QTextCharFormat & 
QConsoleWidget::getInnerCharFormat()const {
	return thisp->textCharFormat;
}

void QConsole::insertText(const QString &t) {
	{
		auto tc = thisp->textCursor();
		tc.clearSelection();
		thisp->setTextCursor(tc);
	}
	auto tc = thisp->textCursor();
	tc.setCharFormat( thisp->getInnerCharFormat());
	tc.insertText(t);
	thisp->setTextCursor(tc);
}

void QConsoleWidget::dragEnterEvent(QDragEnterEvent *e){
    TP::dragEnterEvent(e);

	if(e->isAccepted()){/*调整选区为可编辑区域*/
		QTextCursor tc = this->textCursor();
		if (tc.hasSelection()) {
			if (tc.selectionStart()>= this->promptEndPos_) {
				return;
			}
			else {
				if (tc.selectionEnd()<= this->promptEndPos_) {
					tc.clearSelection();
					this->setTextCursor(tc);
				}
				else {
					auto se_ = tc.selectionEnd();
					tc.setPosition(this->promptEndPos_);
					tc.setPosition(se_,QTextCursor::KeepAnchor);
					this->setTextCursor(tc);
				}
			}
		}
	}

}
void QConsoleWidget::dragMoveEvent(QDragMoveEvent *e){
	
	{/*测试是否在可drop区域*/
		QTextCursor tc = this->cursorForPosition(e->pos());
		if (tc.position() < this->promptEndPos_) {
			e->setAccepted(false);
			return;
		}
	}

    TP::dragMoveEvent(e);
}

void QConsoleWidget::dropEvent(QDropEvent *e){

	{/*测试是否在可drop区域*/
		QTextCursor tc = this->cursorForPosition(e->pos());
		if (tc.position() < this->promptEndPos_) {
			e->setAccepted(false);
			return;
		}
	}

    TP::dropEvent(e);
}
