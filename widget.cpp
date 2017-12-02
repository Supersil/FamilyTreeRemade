#include "widget.h"

#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
	QWidget(parent)
{
	ViewScene * view = new ViewScene;
	QHBoxLayout * lay = new QHBoxLayout;
	lay->addWidget(view);
	setLayout(lay);
}

Widget::~Widget()
{

}
