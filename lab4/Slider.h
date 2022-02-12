#pragma once

#include <QDialog>
#include <QSlider>
#include "Figure.h"

class Slider : public QDialog
{
	Q_OBJECT

public:
	Slider(Figure* f, QWidget* parent);
	void changeAngle();

private:
	QSlider* AngleSlider;
	Figure* figure;
};
