#include "lab4.h"
#include "Figure.h"
#include <QMenuBar>
#include <QCoreApplication>
#include <QContextMenuEvent>
#include <QToolBar>
#include <QActionGroup>
#include <QPainter>

lab4::lab4(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	MainMenu = menuBar()->addMenu(tr("&File"));
	//setGeometry(100, 100, 1280, 720);
	setFixedSize(1280, 720);
	//ui.toolbar = new QToolBar(this);
	clrAction = MainMenu->addAction("&Clear");
	ActionInterClr = MainMenu->addAction("&Delete intersected");
	ActionAdd = ui.toolbar->addAction("&Add");
	ActionDelete = ui.toolbar->addAction("&Delete");
	ActionDelete->setEnabled(false);
	ui.toolbar->addSeparator();
	ActionFigure40 = ui.toolbar->addAction("&Figure 40");
	ActionFigure50 = ui.toolbar->addAction("&Figure 50");
	QActionGroup* group = new QActionGroup(this);
	group->addAction(ActionFigure40);
	group->addAction(ActionFigure50);
	ActionFigure40->setCheckable(true);
	ActionFigure40->setChecked(true);
	ActionFigure50->setCheckable(true);
	//ActionAdd->setEnabled(false);

	setMouseTracking(true);

	connect(ActionFigure40, SIGNAL(triggered()), this,
		SLOT(Figure::SetFigure40()));
	connect(ActionFigure50, SIGNAL(trigerred()), this,
		SLOT(Figure::SetFigure50()));
	connect(ActionAdd, SIGNAL(triggered()), this, SLOT(Add()));
	connect(clrAction, &QAction::triggered, this, &lab4::FullClr);
	connect(ActionInterClr, &QAction::triggered, this, &lab4::InterClr);
	connect(ActionDelete, SIGNAL(triggered()), this, SLOT(Delete()));
}

void lab4::Add()
{
	Figure* f = new Figure(this);
	if (ActionFigure40->isChecked())
	{
		f->SetFigure40(true);
		f->SetFigure50(false);
	}
	else if (ActionFigure50->isChecked())
	{
		f->SetFigure40(false);
		f->SetFigure50(true);
	}
	figures.push_back(f);
	connect(figures[figures.size() - 1], &Figure::signalBack, this,
		&lab4::activateDel);
	repaint();
}

void lab4::activateDel()
{
	ActionDelete->setEnabled(true);
}

void lab4::FullClr()
{
	for (auto elem : figures)
		elem->close();

	figures.clear();
	repaint();
}

bool Intersection(Figure* a, Figure* b) {
	QVector<QPoint> vec1, vec2;

	QPixmap tmp1 = a->grab(QRect(1, 1, a->width(), a->height()));
	QImage image1 = tmp1.toImage();

	//obj->label->setPixmap(QPixmap::fromImage(image1));
	//obj->label->setGeometry(100, 100, 500, 500);

	/*int X1 = a->x(),
	X2 = b->x(),
	Y1 = a->y(),
	Y2 = b->y(),
	X1glob = a->geometry().x();*/

	for (std::size_t x{ 1 }; x < a->width(); ++x)
	{
		for (std::size_t y{ 1 }; y < a->height(); ++y)
		{
			QPoint point(x, y);
			QPoint globPos(x + a->geometry().x(), y + a->geometry().y());
			QColor col = image1.pixelColor(point);

			if (col == QColor(Qt::black))
				vec1.push_back(globPos);
		}
	}

	QPixmap tmp2 = b->grab(QRect(1, 1, b->width(), b->height()));
	QImage image2 = tmp2.toImage();

	for (std::size_t x{ 1 }; x < b->width(); ++x)
	{
		for (std::size_t y{ 1 }; y < b->height(); ++y)
		{
			QPoint point(x, y);
			QPoint globPos(x + b->geometry().x(), y + b->geometry().y());
			QColor col = image2.pixelColor(point);

			if (col == QColor(Qt::black))
				vec2.push_back(globPos);
		}
	}

	QVector<QPoint> inter;

	for (auto elem1 : vec1)
		if (std::find(vec2.begin(), vec2.end(), elem1) != vec2.end())
			return true;

	/*for (auto elem1 : vec1)
	{
		for (auto elem2 : vec2)
		{
			if (elem1 == elem2)
				inter.push_back(elem1);
		}
	}*/

	//obj->points = inter;

	return false;
}

void lab4::InterClr()
{
	if (figures.size() > 1)
	{
		for (std::size_t i{ 0 }; i < figures.size() - 1; ++i)
			for (std::size_t j{ i + 1 }; j < figures.size(); ++j)
			{
				if (!figures[i]->isDeleted()
					&& !figures[j]->isDeleted())
				{
					Figure* r1 = figures[i];
					Figure* r2 = figures[j];
					if (Intersection(r1, r2))
					{
						figures[i]->Intersect() = true;
						figures[j]->Intersect() = true;
					}
				}
			}

		std::size_t k = 0;
		while (k < figures.size())
			if (figures[k]->isIntersected())
			{
				figures[k]->close();
				figures.erase(&figures[k]);
				k = 0;
			}
			else ++k;

		repaint();
	}
}

void lab4::Delete()
{
	for (std::size_t i{ 0 }; i < figures.size(); ++i)
	{
		if (figures[i]->isSelected())
		{
			figures[i]->close();
			figures.erase(&figures[i]);
		}
	}
	ActionDelete->setEnabled(false);
}

void lab4::contextMenuEvent(QContextMenuEvent* event)
{
	MainMenu->exec(event->globalPos());
}

void lab4::mousePressEvent(QMouseEvent* event)
{
	for (auto elem : figures)
		elem->Deselect();
	setMouseTracking(false);
	ActionDelete->setEnabled(false);
	repaint();
}

void lab4::paintEvent(QPaintEvent* event)
{
	QPainter p(this);

	std::size_t cnt{ 0 };
	for (auto elem : figures)
	{
		if (elem->isSelected())
			++cnt;
	}

	for (auto elem : figures)
	{
		if (cnt >= 2)
			elem->Deselect();

		if (!elem->isDeleted())
		{
			elem->update();
			elem->show();
		}
	}
}