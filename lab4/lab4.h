//VARIANT 40

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab4.h"
#include "Figure.h"

#include <QVector>
#include <QPushButton>
#include <QLabel>

class lab4 : public QMainWindow
{
	Q_OBJECT

public:
	lab4(QWidget* parent = Q_NULLPTR);
	void activateDel();

public slots:
	void Add();
	void Delete();
	void FullClr();
	void InterClr();

protected:
	void contextMenuEvent(QContextMenuEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);

private:
	Ui::lab4Class ui;
	QMenu* MainMenu;
	QAction* ActionQuit, * ActionFigure40, * ActionFigure50, * ActionAdd,
		* ActionDelete, * clrAction, * ActionInterClr;
	//QToolBar* toolbar;
	QVector<Figure*> figures;
	//QVector<unsigned short> FigType;
};
