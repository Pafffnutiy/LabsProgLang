#pragma once

#include <QMainWindow>
#include <QtWidgets>
#include "highlighter.h"
#include "CodeEditor.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QApplication* parent = 0);
	~MainWindow();

private slots:
	void newFile();
	void open();
	void saveAs();
	void save();
	void about();
	void undo();
	void redo();
	void selectAll();
	void cut();
	void copy();
	void paste();
	void changeWrap();
	void changeFont();
	void find();
	void replace();
	void findBut(); //Find button in replace dialog
	void replaceBut(); //Replace button in replace dialog
	void findAnother();
	void changedText();
	void panelVisible();
	void statusVisible();
	void numberVisible();
	void isHighlighted();
	void changeBackColor();
	void changeRowColor();
	void cursorPosChanged();
	void setC11();
	void setCPP14();
	void setC18();
	void setCPP17();
	void setCPP20();
	void closeHelp();
	void saveSettings();
	void openStyleFile();
	void editStyleFile();
	void changeStyle();
	void chooseColor();

private:
	Ui::MainWindow* ui;
	CodeEditor* textEdit;
	QAction* newAction, * openAction, * saveAction, * saveAsAction, * exitAction, 
		* aboutAction;
	QMenu* fileMenu, * editMenu, * formatMenu, * viewMenu, * syntaxMenu, 
		* chooseSyntax, * menuText, * styleMenu;
	QAction* undoAction, * redoAction, * copyAction, * cutAction, *pasteAction, * findAction, 
		* findAndReplaceAction, * selectAllAction;
	QAction* wrapAction, * fontAction;
	QAction* backgroundAction, * colorAction, * numberAction, * panelAction,
		* statusAction, * highlightAction;
	QAction* newAction1, * openAction1, * saveAction1, * undoAction1,
		* redoAction1, * copyAction1, * cutAction1, * pasteAction1, 
		* findAction1, * findAndReplaceAction1;
	QDialog* findDialog, * replaceDialog;
	QLineEdit* word, * word2, * word3;
	QAction* C11, * CPP14, * C18, * CPP17, * CPP20;
	QAction* editStyle, * openStyle, * defaultStyle;
	QAction* settingAction;

	QColor backColor = Qt::white, rowColor = Qt::yellow;

	Highlighter* highlite;

	QDialog* help;

	QFileInfo fileinfo;

	QLabel* cursorInfo, * lastInfo, * linesInfo, * wordInfo, * charInfo,
		* sizeInfo;

	QVector<QAction*> stylesAction;

	QColor keywordColor = Qt::darkBlue, singleCommentColor = Qt::red,
		multiCommentColor = Qt::red, quotationColor = Qt::darkGreen,
		functionColor = Qt::blue;

	QActionGroup* stylesGroup;

	QString oldStr = "";

	bool wrapped = false, highlighted = false, panelVis = true, 
		statusVis = true, numberVis = true, isC11 = true, 
		isCPP14 = false, isC18 = false, isCPP17 = false, isCPP20 = false;
};