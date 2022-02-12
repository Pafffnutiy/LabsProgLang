#pragma once
#include <QWidget>
#include <QMenu>
#include <QVariantAnimation>

class Figure : public QWidget
{
	Q_OBJECT;

public:
	explicit Figure(QWidget* parent = nullptr);

	void Deselect();

	int  w() const;
	int& w();

	int  h() const;
	int& h();

	int  x() const;
	int& x();

	int  r1() const;
	int& r1();

	int  r2() const;
	int& r2();

	int  r3() const;
	int& r3();

	int  q1() const;
	int& q1();

	int  q2() const;
	int& q2();

	int  angle() const;
	int& angle();

	qreal sqr() const;
	qreal per() const;

	QString dir() const;
	QString& dir();

	bool isIntersected() const;
	bool& Intersect();

	void SetFigure40(bool b);
	void SetFigure50(bool b);

	void ShowSlider();
	void Moving();
	void Del();
	void Edit();
	bool isDeleted();
	bool isSelected();

	void CalcSquare();
	void CalcPerimeter();

protected:
	void paintEvent(QPaintEvent* event);
	void contextMenuEvent(QContextMenuEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

signals:
	void signalBack();

private:
	bool Selected, figure40 = true, figure50 = false, Deleted = false,
		Intersected = false;

	int W, H, X, R1, R2, R3, Q1, Q2, Angle;
	qreal Square, Perimeter;
	QMenu* contMenu;
	QAction* delAction, * editAction, * movAction, * rotAction;
	QString Direction = "Counterclockwise";
};
