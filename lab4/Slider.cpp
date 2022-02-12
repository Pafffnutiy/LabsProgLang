#include "Slider.h"
#include "Figure.h"
#include <QSlider>
#include <QGridLayout>
#include <QDialog>

Slider::Slider(Figure* f, QWidget* parent)
	: QDialog(parent), figure(f)
{
	AngleSlider = new QSlider(Qt::Horizontal, this);
	AngleSlider->show();
	AngleSlider->setMaximum(180);
	AngleSlider->setMinimum(-180);
	AngleSlider->setValue(0);
	setFixedSize(100, 100);

	QGridLayout* fl = new QGridLayout(this);
	fl->addWidget(AngleSlider, 0, 0);
	setLayout(fl);
	connect(AngleSlider, &QSlider::valueChanged, this, &Slider::changeAngle);
}

void Slider::changeAngle()
{
	figure->angle() = AngleSlider->value();
	figure->update();
}