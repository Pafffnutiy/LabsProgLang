#include "CodeEditor.h"
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QPainter>
#include <QTextBlock>

CodeEditor::CodeEditor(QWidget* parent)
	: QPlainTextEdit(parent)
{
	lineNumberArea = new LineNumberArea(this);

	menuText = createStandardContextMenu();

	menuText->actions()[0]->setEnabled(true);
	menuText->actions()[1]->setEnabled(true);
	menuText->actions()[3]->setEnabled(true);
	menuText->actions()[4]->setEnabled(true);
	menuText->actions()[5]->setEnabled(true);
	menuText->actions()[6]->setEnabled(true);
	menuText->actions()[8]->setEnabled(true);

	QAction* selectWord = new QAction(tr("Select word"), this);
	connect(selectWord, SIGNAL(triggered()), this, SLOT(selectionWord()));
	QAction* selectLine = new QAction(tr("Select line"), this);
	connect(selectLine, SIGNAL(triggered()), this, SLOT(selectionLine()));

	menuText->addAction(selectWord);
	menuText->addAction(selectLine);

	connect(this, SIGNAL(blockCountChanged(int)),
		this, SLOT(updateLineNumberAreaWidth(int)));

	connect(this, SIGNAL(updateRequest(QRect, int)), 
		this, SLOT(updateLineNumberArea(QRect, int)));

	updateLineNumberAreaWidth(0);
}

void CodeEditor::contextMenuEvent(QContextMenuEvent* event)
{
	locPos = event->pos();
	menuText->exec(event->globalPos());
}

void CodeEditor::selectionWord()
{
	QMouseEvent* event = new QMouseEvent(QEvent::MouseButtonDblClick, locPos,
		Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	mouseDoubleClickEvent(event);
}

void CodeEditor::selectionLine()
{
	QMouseEvent* event = new QMouseEvent(QEvent::MouseButtonDblClick, locPos,
		Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QMouseEvent* event2 = new QMouseEvent(QEvent::MouseButtonPress, locPos,
		Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QMouseEvent* event3 = new QMouseEvent(QEvent::MouseButtonRelease, locPos,
		Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

	mouseDoubleClickEvent(event);
	mousePressEvent(event2);
	mouseReleaseEvent(event3);
}

int CodeEditor::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), 
			lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent* e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
	QPainter painter(lineNumberArea);
	painter.fillRect(event->rect(), Qt::lightGray);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)blockBoundingGeometry(block).
		translated(contentOffset()).top();
	int bottom = top + (int)blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, lineNumberArea->width(),
				fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}