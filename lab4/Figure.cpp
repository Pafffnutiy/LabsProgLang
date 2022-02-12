#include "Figure.h"
#include "Slider.h"
#include "EditDialog.h"
#include <QPainter>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <random>
#include <QMenu>
#include <cmath>
#include <numeric>

Figure::Figure(QWidget* parent)
	:QWidget(parent), Selected(false)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());

	/*W = 200;	H = 150; X = 20;
	Q1 = 40; Q2 = 30;
	R1 = 20; R2 = 30; R3 = 40;*/

	Angle = mersenne() % 360;

	W = mersenne() % 200 + 75;
	H = (mersenne() % W + 100) % W + 30;
	X = (mersenne() % H / 3 + 50) % H / 3 + 1;
	Q1 = (mersenne() % W / 4 + 100) % W / 4 + 1;
	Q2 = (mersenne() % W / 4 + 100) % W / 4 + 1;
	R1 = (mersenne() % H / 3 + 50) % H / 3 + 1;
	R2 = (mersenne() % H / 3 + 50) % H / 3 + 1;
	R3 = (mersenne() % H / 3 + 50) % H / 3 + 1;

	contMenu = new QMenu(this);
	delAction = new QAction(tr("&Delete"));
	editAction = new QAction(tr("&Edit"));
	movAction = new QAction(tr("&Move"));
	rotAction = new QAction(tr("&Rotate"));
	contMenu->addAction(editAction);
	contMenu->addAction(movAction);
	contMenu->addAction(rotAction);
	contMenu->addAction(delAction);

	connect(delAction, &QAction::triggered, this, &Figure::Del);
	connect(editAction, &QAction::triggered, this, &Figure::Edit);
	connect(rotAction, &QAction::triggered, this, &Figure::ShowSlider);
	connect(movAction, &QAction::triggered, this, &Figure::Moving);

	resize(sqrt(W * W + H * H), sqrt(W * W + H * H));

	std::size_t curx = mersenne() % (1280 - width());
	std::size_t cury = mersenne() % (720 - height());

	cury = (cury < 50) ? 50 : cury;

	move(curx, cury);

	//QPalette Pal(palette());
	//Pal.setColor(QPalette::Background, Qt::white);
	//setAutoFillBackground(true);
	//setPalette(Pal);

	CalcSquare();
	CalcPerimeter();

	repaint();
}

void Figure::Deselect()
{
	Selected = false;
}

int Figure::h() const
{
	return H;
}

int& Figure::h()
{
	return H;
}

int Figure::x() const
{
	return X;
}

int Figure::w() const
{
	return W;
}

int& Figure::w()
{
	return W;
}

void Figure::SetFigure40(bool b)
{
	figure40 = b;
}

void Figure::SetFigure50(bool b)
{
	figure50 = b;
}

void Figure::ShowSlider()
{
	Slider* obj = new Slider(this, this);
	obj->show();
}

void Figure::Moving()
{
	setMouseTracking(true);
}

void Figure::Del()
{
	Deleted = true;
	close();
	repaint();
}

void Figure::Edit()
{
	EditDialog edit(this, this);
	edit.SetFigure(this);
	if (edit.exec() == edit.Accepted)
	{
		w() = edit.width->value();
		h() = edit.height->value();
		x() = edit.x->value();
		r1() = edit.r1->value();
		r2() = edit.r2->value();
		r3() = edit.r3->value();
		q1() = edit.q1->value();
		q2() = edit.q2->value();
		angle() = edit.Rot->value();
		dir() = edit.DirRot->currentText();
		CalcSquare();
		CalcPerimeter();
		qreal newSide = std::sqrt(std::pow(static_cast<qreal>(W), 2)
			+ std::pow(static_cast<qreal>(H), 2));
		QSize newSize(newSide, newSide);
		resize(newSize);
	}

	update();
}

bool Figure::isDeleted()
{
	return Deleted;
}

bool Figure::isSelected()
{
	return Selected;
}

void Figure::CalcSquare()
{
	qreal SqRect = W * H;

	if (figure40)
	{
		qreal SqA = 0.5 * R1 * R1;
		qreal SqB = 0.5 * R2 * R2;
		qreal SqC = std::_Pi * R3 * R3 / 4;
		qreal SqD = 0.5 * X * X;
		qreal SqE = std::_Pi * Q1 * Q1 / 8;
		qreal SqF = std::_Pi * Q2 * Q2 / 8;
		Square = SqRect - (SqA + SqB + SqC + SqD + SqE);
	}
	else if (figure50)
	{
		qreal SqA = std::_Pi * R2 * R2;
		qreal SqB = std::_Pi * R3 * R3;
		qreal SqC = 0.5 * X * X;
		qreal SqD = std::_Pi * R1 * R1;
		qreal SqE = std::_Pi * Q1 * Q1 / 8;
		qreal SqF = std::_Pi * Q2 * Q2 / 8;
		Square = SqRect - (SqA + SqB + SqC + SqD + SqE + SqF);
	}
}

void Figure::CalcPerimeter()
{
	if (figure40)
	{
		QVector<qreal> parts(9);
		parts[0] = 2 * std::_Pi * R3 / 4;
		parts[1] = W - R3 - R2;
		parts[2] = 2 * std::_Pi * R2 / 4;
		parts[3] = H - R1 - R2;
		parts[4] = 2 * std::_Pi * R1 / 4;
		parts[5] = W - R1 - Q1 - X;
		parts[6] = std::_Pi * Q1;
		parts[7] = sqrt(2) * X;
		parts[8] = H - R3 - X;

		Perimeter = std::accumulate(parts.begin(), parts.end(), 0);
	}
	else if (figure50)
	{
		QVector<qreal> parts(10);
		parts[0] = 2 * std::_Pi * R1 / 4;
		parts[1] = H - R1 - X;
		parts[2] = sqrt(2) * X;
		parts[3] = W - X - Q2 - R3;
		parts[4] = std::_Pi * Q2;
		parts[5] = 2 * std::_Pi * R3 / 4;
		parts[6] = H - R2 - R3;
		parts[7] = 2 * std::_Pi * R2 / 4;
		parts[8] = W - Q1 - R2 - R1;
		parts[9] = std::_Pi * Q1;

		Perimeter = std::accumulate(parts.begin(), parts.end(), 0);
	}
}

void Figure::paintEvent(QPaintEvent* event)
{
	QPainter p(this);

	//p.setPen(Qt::red);
	//p.drawPoint(a);
	//p.setPen(Qt::green);
	//p.drawPoint(b);

	resize(sqrt(W * W + H * H), sqrt(W * W + H * H));

	QPen pen;
	pen.setColor(Qt::black);
	pen.setWidth(3);

	if (Selected)
	{
		pen.setColor(Qt::darkBlue);
	}

	p.setPen(pen);

	p.translate(QPoint(sqrt(W * W + H * H) / 2, sqrt(W * W + H * H) / 2));
	if (Direction == "Clockwise")
		p.rotate(Angle);
	else if (Direction == "Counterclockwise")
		p.rotate(-Angle);
	//Фигура 40
	if (figure40)
	{
		qreal num = W / 2;
		qreal num2 = H / 2;
		p.drawLine(X - num, -num2, (W - Q1) / 2 - num, -num2);
		p.drawArc((W - Q1) / 2 - num, -Q1 / 2 - num2,
			Q1, Q1, 180 * 16, 180 * 16);
		p.drawLine((W + Q1) / 2 - num, -num2, W - R1 - num, -num2);
		p.drawArc(W - 2 * R1 - num, -num2, 2 * R1, 2 * R1, 0, 90 * 16);
		p.drawLine(W - num, R1 - num2, W - num, H - R2 - num2);
		p.drawArc(W - 2 * R2 - num, H - 2 * R2 - num2,
			2 * R2, 2 * R2, 270 * 16, 90 * 16);
		p.drawLine(W - R2 - num, H - num2, R3 - num, H - num2);
		p.drawArc(-R3 - num, H - R3 - num2, 2 * R3, 2 * R3, 0, 90 * 16);
		p.drawLine(-num, H - R3 - num2, -num, X - num2);
		p.drawLine(-num, X - num2, X - num, -num2);
	}
	else if (figure50)
	{
		qreal num = W / 2;
		qreal num2 = H / 2;
		p.drawLine(R1 - num, -num2, (W - Q1) / 2 - num, -num2);
		p.drawArc((W - Q1) / 2 - num, -Q1 / 2 - num2,
			Q1, Q1, 180 * 16, 180 * 16);
		p.drawLine((W + Q1) / 2 - num, -num2, W - R2 - num, -num2);
		p.drawArc(W - R2 - num, -R2 - num2,
			2 * R2, 2 * R2, 180 * 16, 90 * 16);
		p.drawLine(W - num, R2 - num2, W - num, H - R3 - num2);
		p.drawArc(W - R3 - num, H - R3 - num2,
			2 * R3, 2 * R3, 90 * 16, 90 * 16);
		p.drawLine(W - R3 - num, H - num2, (W + Q2) / 2 - num, H - num2);
		p.drawArc((W - Q2) / 2 - num, H - Q2 / 2 - num2,
			Q2, Q2, 0, 180 * 16);
		p.drawLine((W - Q2) / 2 - num, H - num2, X - num, H - num2);
		p.drawLine(X - num, H - num2, -num, H - X - num2);
		p.drawLine(-num, H - X - num2, -num, R1 - num2);
		p.drawArc(-R1 - num, -R1 - num2, 2 * R1, 2 * R1, 270 * 16, 90 * 16);
	}
}

void Figure::contextMenuEvent(QContextMenuEvent* e)
{
	QTransform matrix;

	int ynew, xnew, ynew1, xnew1, ynew2, xnew2, x1, y1;
	qreal ugol = Angle;

	if (Direction == "Clockwise")
		ugol = -Angle;

	matrix = matrix.translate(width() / 2, height() / 2).rotate(-ugol);

	ugol *= std::_Pi / 180;

	x1 = e->x();
	y1 = e->y();
	QPoint newpoint = QPoint(x1, y1) * matrix.inverted();

	if (figure40)
	{
		ynew1 = ((-H + Q1) / 2);
		ynew2 = (H / 2 - R3);
		xnew1 = (-W / 2 + std::max(X, R3));
		xnew2 = W / 2;
	}
	else if (figure50)
	{
		ynew1 = -H / 2 + qMax(qMax(R1, R2), Q1 / 2);
		ynew2 = H / 2 - qMax(qMax(X, Q2 / 2), R3);
		xnew1 = -W / 2 + qMax(X, R1);
		xnew2 = W / 2 - qMax(R2, R3);
	}

	if (newpoint.y() > ynew1 && newpoint.y() < ynew2 &&
		newpoint.x() > xnew1 && newpoint.x() < xnew2)
		contMenu->exec(e->globalPos());
}

void Figure::mousePressEvent(QMouseEvent* e)
{
	QTransform matrix;

	int ynew, xnew, ynew1, xnew1, ynew2, xnew2, x1, y1;
	qreal ugol = Angle;

	if (Direction == "Clockwise")
		ugol = -Angle;

	matrix = matrix.translate(width() / 2, height() / 2).rotate(-ugol);

	ugol *= std::_Pi / 180;

	x1 = e->localPos().x();
	y1 = e->localPos().y();
	QPoint newpoint = QPoint(x1, y1) * matrix.inverted();

	if (figure40)
	{
		ynew1 = ((-H + Q1) / 2);
		ynew2 = (H / 2 - R3);
		xnew1 = (-W / 2 + std::max(X, R3));
		xnew2 = W / 2;
	}
	else if (figure50)
	{
		ynew1 = -H / 2 + qMax(qMax(R1, R2), Q1 / 2);
		ynew2 = H / 2 - qMax(qMax(X, Q2 / 2), R3);
		xnew1 = -W / 2 + qMax(X, R1);
		xnew2 = W / 2 - qMax(R2, R3);
	}

	if (newpoint.y() > ynew1 && newpoint.y() < ynew2 &&
		newpoint.x() > xnew1 && newpoint.x() < xnew2)
	{
		Selected = true;
		setMouseTracking(false);

		signalBack();
	}
	else Selected = false;

	repaint();
}

void Figure::mouseMoveEvent(QMouseEvent* e)
{
	QTransform matrix;
	//a = e->localPos();
	int ynew, xnew, ynew1, xnew1, ynew2, xnew2, x1, y1;
	qreal ugol = Angle;

	if (Direction == "Clockwise")
		ugol = -Angle;

	matrix = matrix.translate(width() / 2, height() / 2).rotate(-ugol);

	ugol *= std::_Pi / 180;

	x1 = e->localPos().x();
	y1 = e->localPos().y();
	QPoint newpoint = QPoint(x1, y1) * matrix.inverted();

	if (figure40)
	{
		ynew1 = ((-H + Q1) / 2);
		ynew2 = (H / 2 - R3);
		xnew1 = (-W / 2 + std::max(X, R3));
		xnew2 = W / 2;
	}
	else if (figure50)
	{
		ynew1 = -H / 2 + qMax(qMax(R1, R2), Q1 / 2);
		ynew2 = H / 2 - qMax(qMax(X, Q2 / 2), R3);
		xnew1 = -W / 2 + qMax(X, R1);
		xnew2 = W / 2 - qMax(R2, R3);
	}

	if (newpoint.y() > ynew1 && newpoint.y() < ynew2 &&
		newpoint.x() > xnew1 && newpoint.x() < xnew2)
	{
		move(e->windowPos().x() - width()  / 2, 
			 e->windowPos().y() - height() / 2);

		if (e->windowPos().x() - width() / 2 > 1280 - geometry().width())
			move(1280 - geometry().width(), 
				e->windowPos().y() - height() / 2);
		if (e->windowPos().y() - height() / 2 < 50)
			move(e->windowPos().x() - width() / 2, 50);
		if (e->windowPos().x() - width() / 2 < 0)
			move(0, e->windowPos().y() - height() / 2);
		if (e->windowPos().y() - width() / 2 > 720 - geometry().height())
			move(e->windowPos().x() - width() / 2,
				720 - geometry().height());

		if ((e->windowPos().x() - width() / 2 >= 1280 - geometry().width())
			&& (e->windowPos().y() - height() / 2 >= 
				720 - geometry().height()))
			move(1280 - geometry().width(), 720 - geometry().height());

		if ((e->windowPos().x() - width() / 2 >= 1280 - geometry().width())
			&& (e->windowPos().y() - height() / 2 <= 50))
			move(1280 - geometry().width(), 50);

		if ((e->windowPos().x() - width() / 2 <= 0)
			&& (e->windowPos().y() - height() / 2 <= 50))
			move(0, 50);

		if ((e->windowPos().x() - width() / 2 <= 0)
			&& (e->windowPos().y() - height() / 2 >= 
				720 - geometry().height()))
			move(0, 720 - geometry().height());
	}
	update();
}

int& Figure::x()
{
	return X;
}

int Figure::r1() const
{
	return R1;
}

int& Figure::r1()
{
	return R1;
}

int Figure::r2() const
{
	return R2;
}

int& Figure::r2()
{
	return R2;
}

int Figure::r3() const
{
	return R3;
}

int& Figure::r3()
{
	return R3;
}

int Figure::q1() const
{
	return Q1;
}

int& Figure::q1()
{
	return Q1;
}

int Figure::q2() const
{
	return Q2;
}

int& Figure::q2()
{
	return Q2;
}

int Figure::angle() const
{
	return Angle;
}

int& Figure::angle()
{
	return Angle;
}

qreal Figure::sqr() const
{
	return Square;
}

qreal Figure::per() const
{
	return Perimeter;
}

QString Figure::dir() const
{
	return Direction;
}

QString& Figure::dir()
{
	return Direction;
}

bool Figure::isIntersected() const
{
	return Intersected;
}

bool& Figure::Intersect()
{
	return Intersected;
}