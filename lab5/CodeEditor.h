#pragma once

#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
	Q_OBJECT

public:
	CodeEditor(QWidget* parent);

	void lineNumberAreaPaintEvent(QPaintEvent* event);
	int lineNumberAreaWidth();

	QWidget* lineNumberArea; // Incapsulation is foo, sorry

protected:
	void resizeEvent(QResizeEvent* event);
	void contextMenuEvent(QContextMenuEvent* event);

private:
	QMenu* menuText;
	QPoint locPos;

private slots:
	void selectionWord();
	void selectionLine();
	void updateLineNumberAreaWidth(int newBlockCount);
	void updateLineNumberArea(const QRect&, int);
};

class LineNumberArea : public QWidget
{
public:
	LineNumberArea(CodeEditor* editor) : QWidget(editor) {
		codeEditor = editor;
	}

	QSize sizeHint() const {
		return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent* event) {
		codeEditor->lineNumberAreaPaintEvent(event);
	}

private:
	CodeEditor* codeEditor;
};
