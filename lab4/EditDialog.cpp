#include "EditDialog.h"
#include <QLabel>
#include <QGridLayout>
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>

EditDialog::EditDialog(Figure* f, QWidget* parent)
	: QDialog(parent), figure(f)
{
	ui.setupUi(this);

	QFrame* frame = new QFrame(this);
	frame->setFrameStyle(QFrame::Box | QFrame::Sunken);

	QLabel* lW = new QLabel(tr("Width"), frame);
	QLabel* lH = new QLabel(tr("Height"), frame);
	QLabel* lX = new QLabel(tr("X"), frame);
	QLabel* lR1 = new QLabel(tr("R1"), frame);
	QLabel* lR2 = new QLabel(tr("R2"), frame);
	QLabel* lR3 = new QLabel(tr("R3"), frame);
	QLabel* lQ1 = new QLabel(tr("Q1"), frame);
	QLabel* lQ2 = new QLabel(tr("Q2"), frame);
	QLabel* lDirRot = new QLabel(tr("Direction of rotation"), frame);
	QLabel* lRot = new QLabel(tr("Rotation"), frame);
	QLabel* lPer = new QLabel(tr("Perimeter"), frame);
	QLabel* lS = new QLabel(tr("Square"), frame);

	DirRot = new QComboBox(frame);
	DirRot->addItem(tr("Counterclockwise"));
	DirRot->addItem(tr("Clockwise"));

	width = new QSpinBox(frame);
	height = new QSpinBox(frame);
	x = new QSpinBox(frame);
	r1 = new QSpinBox(frame);
	r2 = new QSpinBox(frame);
	r3 = new QSpinBox(frame);
	q1 = new QSpinBox(frame);
	q2 = new QSpinBox(frame);
	Rot = new QSpinBox(frame);

	PerimeterLine = new QLineEdit(frame);
	SquareLine = new QLineEdit(frame);
	PerimeterLine->setReadOnly(true);
	SquareLine->setReadOnly(true);

	width->setRange(60, 300);
	height->setRange(24, width->maximum() - 1);
	x->setRange(1, height->maximum() / 3 - 1);
	r1->setRange(1, height->maximum() / 3 - 1);
	r2->setRange(1, height->maximum() / 3 - 1);
	r3->setRange(1, height->maximum() / 3 - 1);
	q1->setRange(1, width->maximum() / 4 - 1);
	q2->setRange(1, width->maximum() / 4 - 1);
	Rot->setRange(0, 359);

	width->setValue(f->w());
	height->setValue(f->h());
	x->setValue(f->x());
	r1->setValue(f->r1());
	r2->setValue(f->r2());
	r3->setValue(f->r3());
	q1->setValue(f->q1());
	q2->setValue(f->q2());
	Rot->setValue(f->angle());
	SquareLine->setText(QString::number(f->sqr()));
	PerimeterLine->setText(QString::number(f->per()));

	QGridLayout* fl = new QGridLayout(frame);
	fl->addWidget(lW, 0, 0);
	fl->addWidget(lH, 1, 0);
	fl->addWidget(lX, 2, 0);
	fl->addWidget(lR1, 3, 0);
	fl->addWidget(lR2, 4, 0);
	fl->addWidget(lR3, 5, 0);
	fl->addWidget(lQ1, 6, 0);
	fl->addWidget(lQ2, 7, 0);
	fl->addWidget(lDirRot, 8, 0);
	fl->addWidget(lRot, 9, 0);
	fl->addWidget(lPer, 10, 0);
	fl->addWidget(lS, 11, 0);
	fl->addWidget(width, 0, 1);
	fl->addWidget(height, 1, 1);
	fl->addWidget(x, 2, 1);
	fl->addWidget(r1, 3, 1);
	fl->addWidget(r2, 4, 1);
	fl->addWidget(r3, 5, 1);
	fl->addWidget(q1, 6, 1);
	fl->addWidget(q2, 7, 1);
	fl->addWidget(DirRot, 8, 1);
	fl->addWidget(Rot, 9, 1);
	fl->addWidget(PerimeterLine, 10, 1);
	fl->addWidget(SquareLine, 11, 1);
	frame->setLayout(fl);

	QPushButton* accbutt = new QPushButton(tr("Accept"), this);
	connect(accbutt, SIGNAL(clicked()), this, SLOT(accept()));

	QGridLayout* l = new QGridLayout(this);
	l->addWidget(frame, 0, 0);
	l->addWidget(accbutt, 1, 0);
	setLayout(l);

	setModal(true);
}

void EditDialog::SetFigure(Figure* f)
{
	figure = f;
	if (figure != nullptr)
	{
		width->setValue(f->w());
		height->setValue(f->h());
		x->setValue(f->x());
		r1->setValue(f->r1());
		r2->setValue(f->r2());
		r3->setValue(f->r3());
		q1->setValue(f->q1());
		q2->setValue(f->q2());
		Rot->setValue(f->angle());
		if (DirRot->currentText() != f->dir())
			DirRot->setCurrentIndex((DirRot->currentIndex() + 1) % 2);
		SquareLine->setText(QString::number(f->sqr()));
		PerimeterLine->setText(QString::number(f->per()));

		height->setRange(24, width->value() - 1);
		x->setRange(1, height->value() / 3 - 1);
		r1->setRange(1, height->value() / 3 - 1);
		r2->setRange(1, height->value() / 3 - 1);
		r3->setRange(1, height->value() / 3 - 1);
		q1->setRange(1, width->value() / 4 - 1);
		q2->setRange(1, width->value() / 4 - 1);
	}
}