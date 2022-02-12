#pragma once

#include "ui_EditDialog.h"
#include "Figure.h"

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>

class EditDialog : public QDialog
{
	Q_OBJECT

public:
	EditDialog(Figure* f, QWidget* parent = Q_NULLPTR);

	void SetFigure(Figure* f);

	QSpinBox* width, * height, * x, * r1, * r2, * r3, * q1, * q2, * Rot;
	QComboBox* DirRot;
	QLineEdit* PerimeterLine, * SquareLine;

private:
	Ui::EditDialog ui;
	Figure* figure;
};
